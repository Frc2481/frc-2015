/*
 * Arm.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: thomasSpeciale
 */

#include "Arm.h"
#include <algorithm>
#include "RobotParameters.h"
#include "CommandBase.h"
#include "Components/PersistedSettings.h"

#define SHOULDER_RAMP_RATE 0.15

Arm::Arm() : Subsystem("Arm"),
		mShoulderEncoder     (new ContinuousEncoder(SHOULDER_ENCODER)),
		mWristEncoder        (new ContinuousEncoder(WRIST_ENCODER)),
		mArmExtention        (new Solenoid(EXTENTION_SOLENOID)),
		mGripperClose        (new Solenoid(GRIPPER_SOLENOID_CLOSE)),
		mGripperOpen         (new Solenoid(GRIPPER_SOLENOID_OPEN)),
		mPivotShoulderTalon  (new DualCANTalon(ARM_SHOULDER_PIVOT_A, ARM_SHOULDER_PIVOT_B, false, true)),
		mPivotWristTalon     (new CANTalon(ARM_WRIST_PIVOT)),
		mPIDShoulder         (new PController(mShoulderEncoder,mPivotShoulderTalon,
								.1,0)),
		mPIDWrist            (new PController(mWristEncoder,mPivotWristTalon,
								PersistedSettings::GetInstance().Get("WRIST_P"),0)),
		mWristOffset(0.0f),
		mNormalLoopCounter(0),
		mPrevWristSetPoint(0),
		mWristStallCounter(0),
		mWristNoEncoderOffset(false),
		mWristOverride(false),
		mShoulderMaxSpeedOutput(SHOULDER_RAMP_RATE),
		mPrevShoulderValue(mShoulderEncoder->GetAngle()),
		mGripperShudderEnabled(false),
		mShoulderWraparoundDetectionCount(0),
		mWristState(NORMAL)
		{

	mGripperShudder = new Notifier(Arm::CallGripperShudder, this);
	mGripperShudder->StartPeriodic(.005);
	mPivotWristTalon->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
//	mPivotShoulderTalon->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);

	mShoulderEncoder->SetOffset(PersistedSettings::GetInstance().Get("SHOULDER_ENCODER_OFFSET", 302.61));
	mWristEncoder->SetOffset(PersistedSettings::GetInstance().Get("WRIST_ENCODER_OFFSET", 11.3716));

	mPIDShoulder->SetInputRange(0.0, 360.0);
	mPIDWrist->SetInputRange(0.0, 360.0);

	mPIDShoulder->SetTolerance(.75);
	mPIDWrist->SetTolerance(1);

	mPIDWrist->SetContinuous(false);
	mPIDShoulder->SetContinuous(true);

	mPIDShoulder->SetOutputRange(-1, 1);

	mPIDWrist->SetOutputRange(-1, 1);
	mPIDWrist->Disable();
	mPIDWrist->Invert();

	mPIDShoulder->Disable();

	mWristStalled = false;
	mWristLocked = false;

	mPIDShoulder->SetStallDetect(true);

//	mPIDShoulder->SetBrakeMode(true);

	mPivotShoulderTalon->GetTalonA()->ConfigRevLimitSwitchNormallyOpen(true);	//A is 13
	mPivotShoulderTalon->GetTalonB()->ConfigFwdLimitSwitchNormallyOpen(true);	//B is 15

	if (PersistedSettings::GetInstance().Get("WRIST_ENCODER_OFFSET_SET", 0) == 0) {
		//mWristNoEncoderOffset = true;
	}
}

void Arm::SetWristOffset(float wristOffset) {
	mWristOffset = wristOffset;
}

void Arm::PeriodicUpdate() {

	double shoulderAngle = GetShoulderAngle();
//	float wristAngle = -mShoulderEncoder->GetAngle() + mWristOffset;
//	while (wristAngle < 0){
	if (mPIDShoulder->GetSetPoint() > shoulderAngle){
		mShoulderMaxSpeedOutput = std::min(mShoulderMaxSpeedOutput + SHOULDER_RAMP_RATE, 1.0);
		mPIDShoulder->SetOutputRange(-mShoulderMaxSpeedOutput, 1.0);
	}
	else {
		mShoulderMaxSpeedOutput = std::max(mShoulderMaxSpeedOutput - SHOULDER_RAMP_RATE, shoulderAngle < 35 ? -.6 : -1.0);
		mPIDShoulder->SetOutputRange(-1.0, -mShoulderMaxSpeedOutput);
	}

//	}

//	if (mPIDShoulder->OnTarget()){
//		mPIDShoulder->SetP(.00000000001);
//	}
//	else {
//		mPIDShoulder->SetP(.5);
//	}

	/*
	 * The Goal of this Code is to insure that the shoulder does not wraparound at the bottom
	 * of the arm. it checks if the encoder value is decreasing and the motors are positive.
	 */
#define SHOULDER_WRAPAROUND_DETECTION 1
#ifdef SHOULDER_WRAPAROUND_DETECTION
	if (mPivotShoulderTalon->Get() > 0 &&
			mPrevShoulderValue > shoulderAngle &&
			shoulderAngle > 45){
		mShoulderWraparoundDetectionCount++;
	} else {
		mShoulderWraparoundDetectionCount = 0;
	}

	if (mShoulderWraparoundDetectionCount > 3) {
		mPIDShoulder->Disable();
	}

	mPrevShoulderValue = shoulderAngle;
#endif

	/*
	 * The goal of this code is to detect the gripper going above max height and forcing
	 * it back down. Additionally, if we are too high, open the gripper so that the can is
	 * pushed up and not the wrist.
	 */
//#define WRIST_DRIFT_DETECTION 1
#ifdef WRIST_DRIFT_DETECTION
	if (mShoulderEncoder->GetAngle() < 20) {
		if (mWristEncoder->GetAngle() < 262 && CommandBase::stacker->GetToteCount() > 3){   //4 to 3
			mWristState = CRITICAL;
		}
		else if (mWristEncoder->GetAngle() < 267){
			mWristState = WARNING;
		}
	}

	if (mWristState == CRITICAL){
		if (CommandBase::stacker->GetToteCount() < 4){
			CloseGripper();
		}
		else {
			OpenGripper();
		}
		mPIDWrist->SetSetpoint(270);
		mPIDWrist->Enable();
	}
	else if (mWristState == WARNING){
		mPIDWrist->SetSetpoint(270);
		mPIDWrist->Enable();
	}

	if (mWristState == CRITICAL){
		mWristState = POST_CRITICAL;
		mNormalLoopCounter = 0;
	}
	else if (mWristState == WARNING){
		mWristState = POST_WARNING;
		mNormalLoopCounter = 0;
	}

	if (mWristState == POST_CRITICAL || mWristState == POST_WARNING){
		mNormalLoopCounter++;
	}

	if (mNormalLoopCounter > 10){
		if (mWristState == POST_CRITICAL){
			CloseGripper();
		}
		mPIDWrist->Disable();
		mWristState = NORMAL;
	}

	SmartDashboard::PutNumber("WristSafetyState", mWristState);
	SmartDashboard::PutNumber("WristSafetyCount", mNormalLoopCounter);
#endif

	/*
	 *Code to insure that the arm does not extend over our max height
	 */
#define ARM_EXTENTION_SAFETY 1
#ifdef ARM_EXTENTION_SAFETY
	if (GetShoulderAngle() < 50){
		mArmExtention->Set(false);
	}
#endif


//	mWristCurrent.add(mPivotWristTalon->GetOutputCurrent());
//	if (mWristCurrent.avg() > 7.5){

#define WRIST_STALL_DETECTION 1
#ifdef WRIST_STALL_DETECTION
	if (mPivotWristTalon->GetOutputCurrent() > 7.5) {
		mWristStallCounter++;
	} else {
		mWristStallCounter = 0;
	}

	if (mWristStallCounter > 10) {
		if (!mWristStalled && !mWristNoEncoderOffset){
			PersistedSettings::GetInstance().Set("WRIST_STALLED_COUNT",
				PersistedSettings::GetInstance().Get("WRIST_STALLED_COUNT", 0) + 1);
		}
		mWristStalled = true;
	}

	if (mWristStalled || mWristNoEncoderOffset) {
		mPivotWristTalon->Set(0.0);
		mPIDWrist->Disable();
	}
#endif

	if (mWristLocked && !mWristOverride){
		if (mPIDShoulder->GetSetPoint() < shoulderAngle &&
				shoulderAngle < 40) {
			SetWristPosition(270);
		} else {
			SetWristPosition(GetParallel());
		}
		mPIDWrist->SetP(.08);
	} else {
		mPIDWrist->SetP(.05);
	}
	//mPIDWrist->SetSetpoint(wristAngle);

//	if (mPIDShoulder->GetError() > 30){
//		mPIDShoulder->ResetError();
//	}
//	if (mPIDWrist->GetError() > 30){
//		mPIDWrist->ResetError();
//	}

//	if (mShoulderEncoder->GetAngle() > 15){
//		RetractArm();
//	}

//	if (mPIDWrist->OnTarget()) {
//		mPIDWrist->Disable();
//	}

//	if (mPIDWrist->IsEnabled()) {
//		static bool first = true;
//		if (first) {
//			first = false;
//			mShoulderEncoder->SetOffset(PersistedSettings::GetInstance().Get("SHOULDER_ENCODER_OFFSET"));
//			mWristEncoder->SetOffset(PersistedSettings::GetInstance().Get("WRIST_ENCODER_OFFSET"));
//		}
//	}

#ifdef DEBUGGING

//	SmartDashboard::PutData("Wrist PID", mPIDWrist);
//	SmartDashboard::PutData("Shoulder PID", mPIDShoulder);
	SmartDashboard::PutNumber("Current Arm Position", mShoulderEncoder->GetAngle());
	SmartDashboard::PutNumber("Current Arm Position Raw", mShoulderEncoder->GetRawAngle());
	SmartDashboard::PutNumber("Current Wrist Position", mWristEncoder->GetAngle());
	SmartDashboard::PutNumber("Current Wrist Position Raw", mWristEncoder->GetRawAngle());
	SmartDashboard::PutNumber("Wrist Set Point", mPIDWrist->GetSetPoint());
	SmartDashboard::PutBoolean("Wrist Stalled", mWristStalled);
//	SmartDashboard::PutBoolean("Gripper Close Solenoid", mGripperClose->Get());
//	SmartDashboard::PutBoolean("Gripper Open Solenoid", mGripperOpen->Get());
//	SmartDashboard::PutBoolean("Extender Solenoid", mArmExtention->Get());
	SmartDashboard::PutNumber("Wrist Motor Speed", mPivotWristTalon->Get());
	SmartDashboard::PutNumber("Shoulder Motor Speed", mPivotShoulderTalon->Get());
	SmartDashboard::PutNumber("Wrist Current Draw", mPivotWristTalon->GetOutputCurrent());
	SmartDashboard::PutNumber("Wrist Offset", mWristEncoder->GetOffset());
	SmartDashboard::PutBoolean("Shoulder On Target", mPIDShoulder->OnTarget());
	SmartDashboard::PutNumber("Shoulder Current Draw", mPivotShoulderTalon->GetOutputCurrent());

	//mPIDShoulder->SetP(shoulderP);
	//mPIDWrist->SetP(wristP);
#endif
}

void Arm::SetPivotArmAbs(float position) {
	mPIDShoulder->ResetStalled();
	mPIDShoulder->SetSetpoint(position);
	mShoulderMaxSpeedOutput = SHOULDER_RAMP_RATE * (position > GetShoulderAngle() ? 1.0 : -1.0);
	mPIDShoulder->Enable();
	SmartDashboard::PutNumber("Arm SetPoint", position);
}

void Arm::SetPivotArmRelative(float position) {
	SetPivotArmAbs(position + GetShoulderAngle());
}

void Arm::CloseGripper() {
	mGripperClose->Set(false);
	mGripperOpen->Set(true);
}

void Arm::OpenGripper() {
	mGripperClose->Set(true);
	mGripperOpen->Set(false);
}

void Arm::ExtendArm() {
//	if (mShoulderEncoder->GetAngle() > 60){
		mArmExtention->Set(true);
//	}
}

void Arm::RetractArm() {
	mArmExtention->Set(false);
}

bool Arm::IsExtended(){
	return mArmExtention->Get();
}

bool Arm::IsGripper(){
	return mGripperClose->Get();
}

bool Arm::IsArmOnTarget() {
	return mPIDShoulder->OnTarget() || !mPIDShoulder->IsEnabled() || mPIDShoulder->GetStalled();
}

void Arm::StopPivotArm() {
	mPIDShoulder->Disable();
	if (GetShoulderAngle() < 10) {
		mWristOverride = false;
	}
}

//float Arm::GetPivotPos() {
//	return mPivotShoulderTalon->GetAnalogIn();
//}

float Arm::GetRawShoulderAngle() {
	return mShoulderEncoder->GetRawAngle();
}

float Arm::GetRawWristAngle() {
	return mWristEncoder->GetRawAngle();
}

void Arm::SetShoulderEncoderOffset(float shoulderOffset) {
	mShoulderEncoder->SetOffset(shoulderOffset);
}

void Arm::SetWristOffsetRelative(int offsetWrist) {
	mWristOffset = std::min(std::max(mWristOffset + offsetWrist, -90), 90);
}

void Arm::StopPivotWrist() {
	mPIDWrist->Disable();
}

void Arm::SetWristEncoderOffset(float wristOffset) {
	mWristEncoder->SetOffset(wristOffset);
}

bool Arm::IsWristOnTarget() {
	return mPIDWrist->OnTarget();
}

void Arm::SetWristPosition(double pos, bool override) {
	//FIXME mWristNoEncoderOffset check is not right.
	if ((!mWristStalled || mWristNoEncoderOffset) && mWristState == NORMAL){
		double minWrist = 90;
		if (GetShoulderAngle() < 45) {
			minWrist = GetParallel();
		}
		pos = std::min(std::max(pos , minWrist), 270.0);

		if (override) {
			mWristOverride = true;
		}

		//If the wrist is in override then force it to 270.
		//This should result in no move.
		if (mWristOverride) {
			pos = 265;
		}
		mPIDWrist->SetSetpoint(pos);
		mPIDWrist->Enable();
	}
}

void Arm::SetWristManual(double speed) {
	mPIDWrist->Disable();
	if (mGripperClose->Get()) {
		mPivotWristTalon->Set(-speed);
	}
	else {
		mPivotWristTalon->Set(-speed * .5);
	}
}

bool Arm::GetStalled() {
	return mWristStalled;
}

void Arm::SetStalled(bool stalled) {
	mWristStalled = stalled;
}

void Arm::SetWristLinked(bool linked) {
	if(mWristLocked != linked){
		if(linked){
			mPIDWrist->Enable();
		}
		else{
			mPIDWrist->Disable();
		}
	}
	mWristLocked = linked;
}

double Arm::GetParallel() {
	double encAngle = GetShoulderAngle();
	encAngle = encAngle > 150.0 ? 0.5 : encAngle;

	if (encAngle < 10){
		return 270;
	}
	else {
		return -encAngle + 265;
	}
}

void Arm::SetShoulderManual(double speed) {
	mPIDShoulder->Disable();
	mPivotShoulderTalon->Set(speed * .4);
}

float Arm::GetShoulderAngle() {
	double a = mShoulderEncoder->GetAngle();
	a = a > 200 ? 0 : a;
	return a;
}

float Arm::GetWristAngle() {
	return mWristEncoder->GetAngle();
}

void Arm::CallGripperShudder(void *gripperShudder)
{
	Arm *arm = (Arm*) gripperShudder;
	arm->GripperShudder();
}

void Arm::GripperShudder() {
	static int loopCount = 0;

	if (mGripperShudderEnabled){
		loopCount++;
		if (loopCount < 8){
			OpenGripper();
		}
		else if (loopCount < 15) {
			CloseGripper();
		}
		loopCount %= 15;
	}
}

void Arm::SetGripperShudder(bool b) {
	mGripperShudderEnabled = b;
}

bool Arm::GetGripperShudder() {
	return mGripperShudderEnabled;
}
