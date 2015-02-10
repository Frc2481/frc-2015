/*
 * Lift2481.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: Team2481
 */

#include "LiftPIDOutput2481.h"
#include "RobotParameters.h"

LiftPIDOutput2481::LiftPIDOutput2481(int motor, DigitalInput* bot,
		DigitalInput* top) {
	mMotor = new DualCANTalon(motor, motor + 1, false, true);
	mBottomLimit = bot;
	mTopLimit = top;
	mInverted = false;
}

LiftPIDOutput2481::~LiftPIDOutput2481() {
	delete mMotor;
}

void LiftPIDOutput2481::PIDWrite(float output) {
	Set(output);
}

void LiftPIDOutput2481::Set(float output) {
	if (output > 0 && mTopLimit->Get()){
		output = 0;
	}
	else if (output < 0 && mBottomLimit->Get()){
		output = 0;
	}
	if (mInverted){
		output *= -1;
	}
	mMotor->Set(output);
}

void LiftPIDOutput2481::InvertMotor(bool invert) {
	mInverted = invert;
}

float LiftPIDOutput2481::GetMotorCurrent() {
	return mMotor->GetOutputCurrent();
}
