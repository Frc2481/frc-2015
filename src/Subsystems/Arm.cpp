/*
 * Arm.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: thomasSpeciale
 */

#include "Arm.h"
#include <algorithm>
#include "RobotParameters.h"

Arm::Arm() : Subsystem("Arm"),
		mShoulderEncoder     (new ContinuousEncoder(SHOULDER_ENCODER)),
		mWristEncoder        (new ContinuousEncoder(WRIST_ENCODER)),
		mArmExtention        (new Solenoid(EXTENTION_SOLENOID)),
		mGripper             (new Solenoid(GRIPPER_SOLENOID)),
		mPivotShoulderTalon  (new CANTalon(ARM_SHOULDER_PIVOT)),
		mPivotWristTalon     (new CANTalon(ARM_WRIST_PIVOT)),
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

	mPIDShoulder->SetInputRange(0.0, 360.0);
	mPIDWrist->SetInputRange(0.0, 360.0);

	mPIDShoulder->SetAbsoluteTolerance(3.0);
	mPIDWrist->SetAbsoluteTolerance(3.0);

	mPIDWrist->SetOutputRange(-.5, .5);
}

void Arm::SetWristOffset(float wristOffset) {
	mWristOffset = wristOffset;
}

void Arm::PeriodicUpdate() {

	printf("%d \n", IsExtended());

	float wristAngle = -mShoulderEncoder->GetAngle() + mWristOffset;
	while (wristAngle < 0){
		wristAngle += 360;
	}
	mPIDWrist->SetSetpoint(wristAngle);

	if (mPIDShoulder->GetError() > 30){
		mPIDShoulder->ResetError();
	}
	if (mPIDWrist->GetError() > 30){
		mPIDWrist->ResetError();
	}

	if (mShoulderEncoder->GetAngle() > 15){
		RetractArm();
	}

#ifdef DEBUGGING

	float shoulderP = Preferences::GetInstance()->GetFloat("SHOULDER_P", .066);
	float shoulderI = Preferences::GetInstance()->GetFloat("SHOULDER_I", .001);
	float wristP = Preferences::GetInstance()->GetFloat("WRIST_P", .066);
	float wristI = Preferences::GetInstance()->GetFloat("WRIST_I", .001);

	SmartDashboard::PutData("Wrist PID", mPIDWrist);
	SmartDashboard::PutData("Shoulder PID", mPIDShoulder);
	SmartDashboard::PutNumber("current arm position", mShoulderEncoder->GetAngle());
	SmartDashboard::PutBoolean("gripper solenoid", mGripper->Get());
	SmartDashboard::PutBoolean("Extender Solenoid", mArmExtention->Get());

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
	if (mShoulderEncoder->GetAngle() <= 15){
		mArmExtention->Set(true);
	}
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

void Arm::SetWristOffsetRelative(int offsetWrist) {
	mWristOffset = std::min(std::max(mWristOffset + offsetWrist, -90), 90);

}

void Arm::StopPivotWrist() {
	mPIDWrist->Disable();
}

void Arm::SetWristEncoderOffset(float wristOffset) {
	mWristEncoder->SetOffset(wristOffset);
}
