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

Arm::Arm() : Subsystem("Arm"),
		mShoulderEncoder     (new ContinuousEncoder(SHOULDER_ENCODER)),
		mWristEncoder        (new ContinuousEncoder(WRIST_ENCODER)),
		mArmExtention        (new Solenoid(EXTENTION_SOLENOID)),
		mPivotShoulderTalon  (new CANTalon(ARM_SHOULDER_PIVOT)),
		mGripperClose        (new Solenoid(GRIPPER_SOLENOID_CLOSE)),
		mGripperOpen         (new Solenoid(GRIPPER_SOLENOID_OPEN)),
		mPivotWristTalon     (new CANTalon(ARM_WRIST_PIVOT)),
		mPIDShoulder         (new PController(mShoulderEncoder,mPivotShoulderTalon,
								.8,0)),
		mPIDWrist            (new PController(mWristEncoder,mPivotWristTalon,
								PersistedSettings::GetInstance().Get("WRIST_P"),0)),
		mWristOffset(0.0f),
		mNormalLoopCounter(0),
		mPrevWristSetPoint(0),
		mWristStallCounter(0),
		mWristNoEncoderOffset(false),
		mWristOverride(false),
		mDummyPID(new PIDController(.05,.1,.01,NULL,NULL)),
		mGripperShudderEnabled(false),
		mWristState(NORMAL)
		{

	SmartDashboard::PutData("WristPID", mDummyPID);
	mGripperShudder = new Notifier(Arm::CallGripperShudder, this);
	mGripperShudder->StartPeriodic(.005);
	mPivotWristTalon->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	mPivotShoulderTalon->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);

	mShoulderEncoder->SetOffset(PersistedSettings::GetInstance().Get("SHOULDER_ENCODER_OFFSET", 302.61));
	mWristEncoder->SetOffset(PersistedSettings::GetInstance().Get("WRIST_ENCODER_OFFSET", 11.3716));

	mPIDShoulder->SetInputRange(0.0, 360.0);
	mPIDWrist->SetInputRange(0.0, 360.0);

	mPIDShoulder->SetTolerance(.75);
	mPIDWrist->SetTolerance(2);

	mPIDWrist->SetContinuous(false);
	mPIDShoulder->SetContinuous(true);

	mPIDWrist->SetOutputRange(-1, 1);
	mPIDWrist->Disable();
	mPIDWrist->Invert();

	mPIDShoulder->Disable();

	mWristStalled = false;
	mWristLocked = false;

	mPIDShoulder->SetStallDetect(true);

//	mPIDShoulder->SetBrakeMode(true);

	if (PersistedSettings::GetInstance().Get("WRIST_ENCODER_OFFSET_SET", 0) == 0) {
		//mWristNoEncoderOffset = true;
	}
}

void Arm::SetWristOffset(float wristOffset) {
	mWristOffset = wristOffset;
}

void Arm::PeriodicUpdate() {

//	float wristAngle = -mShoulderEncoder->GetAngle() + mWristOffset;
//	while (wristAngle < 0){

//	}

//	if (mPIDShoulder->OnTarget()){
//		mPIDShoulder->SetP(.00000000001);
//	}
//	else {
//		mPIDShoulder->SetP(.5);
//	}

	/*
	 * The goal of this code is to detect the gripper going above max height and forcing
	 * it back down. Additionally, if we are too high, open the gripper so that the can is
	 * pushed up and not the wrist.
	 */
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
	//End Gripper Height Detection
#endif


	if (mShoulderEncoder->GetAngle() < 50){
		mArmExtention->Set(false);
	}

//	mWristCurrent.add(mPivotWristTalon->GetOutputCurrent());
//	if (mWristCurrent.avg() > 7.5){
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

//	if (!mGripper->Get()){
//		mPIDWrist->SetP(.5);
//	}
//	else {
		mPIDWrist->SetP(mDummyPID->GetP());
//	}

	if (mWristLocked && !mWristOverride){
		SetWristPosition(GetParallel());
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
	SmartDashboard::PutBoolean("Gripper Close Solenoid", mGripperClose->Get());
	SmartDashboard::PutBoolean("Gripper Open Solenoid", mGripperOpen->Get());
	SmartDashboard::PutBoolean("Extender Solenoid", mArmExtention->Get());
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
	mPIDShoulder->Enable();
	SmartDashboard::PutNumber("Arm SetPoint", position);
}

void Arm::SetPivotArmRelative(float position) {
	SetPivotArmAbs(position + mShoulderEncoder->GetAngle());
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
	return mPIDShoulder->OnTarget() || mPIDShoulder->GetStalled();
}

void Arm::StopPivotArm() {
	mPIDShoulder->Disable();
	if (mShoulderEncoder->GetAngle() < 10) {
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
		if (mShoulderEncoder->GetAngle() < 45) {
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
	double encAngle = mShoulderEncoder->GetAngle();
	encAngle = encAngle > 150.0 ? 0.5 : encAngle;

	if (encAngle < 10){
		return 270;
	}
	else {
		return -encAngle + 275;
	}
}

void Arm::SetShoulderManual(double speed) {
	mPIDShoulder->Disable();
	mPivotShoulderTalon->Set(speed);
}

float Arm::GetShoulderAngle() {
	return mShoulderEncoder->GetAngle();
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
