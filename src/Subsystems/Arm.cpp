/*
 * Arm.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: thomasSpeciale
 */

#include "Arm.h"
#include <algorithm>
#include "RobotParameters.h"

Arm::Arm(int armExtentionID, int gripperID, uint32_t shoulderEncoderID,
		uint32_t wristEncoderID, int shoulderTalonID, int wristTalonID):
		Subsystem("Arm"),
		mShoulderEncoder     (new ContinuousEncoder(shoulderEncoderID)),
		mWristEncoder        (new ContinuousEncoder(wristEncoderID)),
		mArmExtention        (new Solenoid(armExtentionID)),
		mGripper             (new Solenoid(gripperID)),
		mPivotShoulderTalon  (new CANTalon(shoulderTalonID)),
		mPivotWristTalon     (new CANTalon(wristTalonID)),
		mPIDShoulder         (new PIDController2481(
								Preferences::GetInstance()->GetFloat("SHOULDER_P", .066),
								Preferences::GetInstance()->GetFloat("SHOULDER_I", .001),
								0,mShoulderEncoder,mPivotShoulderTalon)),
		mPIDWrist            (new PIDController2481(
								Preferences::GetInstance()->GetFloat("WRIST_P", .066),
								Preferences::GetInstance()->GetFloat("WRIST_I", .001),
								0,mWristEncoder,mPivotWristTalon)),
		mWristOffset(0.0f)
		{

	mShoulderEncoder->SetOffset(Preferences::GetInstance()->GetFloat("SHOULDER_ENCODER_OFFSET", 0));
	mWristEncoder->SetOffset(Preferences::GetInstance()->GetFloat("WRIST_ENCODER_OFFSET", 0));
}

void Arm::SetWristOffset(float wristOffset) {
	mWristOffset = wristOffset;
}

void Arm::PeriodicUpdate() {

	mPIDWrist->SetSetpoint(-mShoulderEncoder->GetAngle() + mWristOffset);

	if (mPIDShoulder->GetError() > 30){
		mPIDShoulder->ResetError();
	}
	if (mPIDWrist->GetError() > 30){
		mPIDWrist->ResetError();
	}

#ifdef DEBUGGING

	float shoulderP = Preferences::GetInstance()->GetFloat("SHOULDER_P", .066);
	float shoulderI = Preferences::GetInstance()->GetFloat("SHOULDER_I", .001);
	float wristP = Preferences::GetInstance()->GetFloat("WRIST_P", .066);
	float wristI = Preferences::GetInstance()->GetFloat("WRIST_I", .001);

	mPIDShoulder->SetPID(shoulderP, shoulderI, 0);
	mPIDWrist->SetPID(wristP, wristI, 0);
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
	mGripper->Set(true);
}

void Arm::OpenGripper() {
	mGripper->Set(false);
}

void Arm::ExtendArm() {
	mArmExtention->Set(true);
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
	mPivotShoulderTalon->Disable();
}

float Arm::GetPivotPos() {
	return mPivotShoulderTalon->GetAnalogIn();
}

float Arm::GetRawShoulderAngle() {
	return mShoulderEncoder->GetRawAngle();
}

float Arm::GetRawWristAngle() {
	return mWristEncoder->GetRawAngle();
}

void Arm::SetShoulderEncoderOffset(float shoulderOffset) {
	mShoulderEncoder->SetOffset(shoulderOffset);
}

void Arm::SetWristEncoderOffset(float wristOffset) {
	mWristEncoder->SetOffset(wristOffset);
}
