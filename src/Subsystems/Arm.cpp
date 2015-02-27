/*
 * Arm.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: thomasSpeciale
 */

#include "Arm.h"
#include <algorithm>
#include "RobotParameters.h"
#include "Components/PersistedSettings.h"

Arm::Arm() : Subsystem("Arm"),
		mShoulderEncoder     (new ContinuousEncoder(SHOULDER_ENCODER)),
		mWristEncoder        (new ContinuousEncoder(WRIST_ENCODER)),
		mArmExtention        (new Solenoid(EXTENTION_SOLENOID)),
		mGripper             (new Solenoid(GRIPPER_SOLENOID)),
		mPivotShoulderTalon  (new CANTalon(ARM_SHOULDER_PIVOT)),
		mPivotWristTalon     (new CANTalon(ARM_WRIST_PIVOT)),
		mPIDShoulder         (new PController(mShoulderEncoder,mPivotShoulderTalon,
								.7,.01)),
		mPIDWrist            (new PController(mWristEncoder,mPivotWristTalon,
								PersistedSettings::GetInstance().Get("WRIST_P"),0)),
		mWristOffset(0.0f)
		{

	mPivotWristTalon->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	mPivotShoulderTalon->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);

	mShoulderEncoder->SetOffset(PersistedSettings::GetInstance().Get("SHOULDER_ENCODER_OFFSET"));
	mWristEncoder->SetOffset(PersistedSettings::GetInstance().Get("WRIST_ENCODER_OFFSET"));

	mPIDShoulder->SetInputRange(0.0, 360.0);
	mPIDWrist->SetInputRange(0.0, 360.0);

	mPIDShoulder->SetTolerance(1.5);
	mPIDWrist->SetTolerance(5.0);

	mPIDWrist->SetContinuous(false);
	mPIDShoulder->SetContinuous(true);

	mPIDWrist->SetOutputRange(-1, 1);
	mPIDWrist->Disable();
	mPIDWrist->Invert();

	mPIDShoulder->Disable();

	mWristStalled = false;
	mWristLocked = false;

//	mPIDShoulder->SetBrakeMode(true);
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

	if (mShoulderEncoder->GetAngle() < 50){
		mArmExtention->Set(false);
	}

	if (mPivotWristTalon->GetOutputCurrent() > 14.5){
		mWristStalled = true;
	}

	if (mWristStalled == true) {
		mPivotWristTalon->Set(0.0);
		mPIDWrist->Disable();
	}

//	if (!mGripper->Get()){
//		mPIDWrist->SetP(.5);
//	}
//	else {
		mPIDWrist->SetP(.02);
//	}

	if (mWristLocked){
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

	float shoulderP = PersistedSettings::GetInstance().Get("SHOULDER_P");
	float shoulderI = PersistedSettings::GetInstance().Get("SHOULDER_I");
	float wristP = PersistedSettings::GetInstance().Get("WRIST_P");
	float wristI = PersistedSettings::GetInstance().Get("WRIST_I");

//	SmartDashboard::PutData("Wrist PID", mPIDWrist);
//	SmartDashboard::PutData("Shoulder PID", mPIDShoulder);
	SmartDashboard::PutNumber("Current Arm Position", mShoulderEncoder->GetAngle());
	SmartDashboard::PutNumber("Current Arm Position Raw", mShoulderEncoder->GetRawAngle());
	SmartDashboard::PutNumber("Current Wrist Position", mWristEncoder->GetAngle());
	SmartDashboard::PutNumber("Current Wrist Position Raw", mWristEncoder->GetRawAngle());
	SmartDashboard::PutNumber("Wrist Set Point", mPIDWrist->GetSetPoint());
	SmartDashboard::PutBoolean("Wrist Stalled", mWristStalled);
	SmartDashboard::PutBoolean("Gripper Solenoid", mGripper->Get());
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
	mPIDShoulder->SetSetpoint(position);
	mPIDShoulder->Enable();
}

void Arm::SetPivotArmRelative(float position) {
	SetPivotArmAbs(position + mShoulderEncoder->GetAngle());
}

void Arm::CloseGripper() {
	mGripper->Set(false);
}

void Arm::OpenGripper() {
	mGripper->Set(true);
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
	return mGripper->Get();
}

bool Arm::IsArmOnTarget() {
	return mPIDShoulder->OnTarget();
}

void Arm::StopPivotArm() {
	mPIDShoulder->Disable();
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

void Arm::SetWristPosition(double pos) {
	if (!mWristStalled){
		double minWrist = 90;
		if (mShoulderEncoder->GetAngle() < 45) {
			minWrist = GetParallel();
		}
		pos = std::min(std::max(pos , minWrist), 270.0);
		mPIDWrist->SetSetpoint(pos);
		mPIDWrist->Enable();
	}
}

void Arm::SetWristManual(double speed) {
	mPIDWrist->Disable();
	mPivotWristTalon->Set(-speed * .5);
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
