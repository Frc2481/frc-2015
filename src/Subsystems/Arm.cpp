/*
 * Arm.cpp
 *
 *  Created on: Jan 17, 2015
 *      Author: thomasSpeciale
 */

#include "Arm.h"
#include <algorithm>

Arm::Arm(int armExtentionID, int gripperID, int pivotRightTalonID,
		int pivotLeftTalonID, int gripperTalonID):
		Subsystem("Arm"),
		mArmExtention(new Solenoid(armExtentionID)),
		mGripper(new Solenoid(gripperID)),
		mPivotArmRightTalon(new CANTalon(pivotRightTalonID)),
		mPivotArmLeftTalon(new CANTalon(pivotLeftTalonID)),
		mPivotGripperTalon(new CANTalon(gripperTalonID)),
		mArmPosition(mPivotArmLeftTalon->GetAnalogIn()),
		mGripperPosition(mPivotGripperTalon->GetAnalogIn()),
		mLocked(true)
		{
}

float max(float a, float b) {
	if (a > b)
		return a;
	return b;
}

void Arm::SetPivotArmAbs(float position) {

	mArmPosition = std::fmin(5, std::fmax(0, position));

	mPivotArmRightTalon->Set(mArmPosition);
	mPivotArmLeftTalon->Set(mArmPosition);
	mPivotArmRightTalon->EnableControl();
	mPivotArmLeftTalon->EnableControl();
}


void Arm::SetPivotArmRelative(float position) {
	mArmPosition += position;
	SetPivotArmAbs(mArmPosition);
}

void Arm::CloseGripper() {
	mGripper->Set(true);
}

void Arm::OpenGripper() {
	mGripper->Set(false);
}

void Arm::SetWristAbs(float position) {
	mGripperPosition = std::fmin(5, std::fmax(0, position));

	mPivotGripperTalon->Set(mGripperPosition);
}

void Arm::ExtendArm() {
	mArmExtention->Set(true);
}

void Arm::RetractArm() {
	mArmExtention->Set(false);
}

bool Arm::IsLiftOnTarget() {
	int rError = mPivotArmRightTalon->GetClosedLoopError();
	int lError = mPivotArmLeftTalon->GetClosedLoopError();
	return rError < 1 && lError < 1;
}

void Arm::StopPivotArm() {
	mPivotArmLeftTalon->Disable();
	mPivotArmRightTalon->Disable();
}

bool Arm::IsLocked() {
	return mLocked;
}

float Arm::GetPivotPos() {
	return mPivotArmLeftTalon->GetAnalogIn();
}

void Arm::ToggleLock(){
	mLocked = !mLocked;
}


