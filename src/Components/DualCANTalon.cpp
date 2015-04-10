/*
 * DualCANTalon.cpp
 *
 *  Created on: Jan 29, 2015
 *      Author: Team2481
 */

#include <Components/DualCANTalon.h>


DualCANTalon::DualCANTalon(int motorA, int motorB, bool AInvert, bool BInvert, bool ramp, bool motorBrake) {
	mAMotor = new CANTalon(motorA);
	mBMotor = new CANTalon(motorB);
	mAInverted = AInvert;
	mBInverted = BInvert;

	if(motorBrake){
		mAMotor->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
		mBMotor->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	}

	if(ramp){
		mAMotor->SetVoltageRampRate(12);
		mBMotor->SetVoltageRampRate(12);
	}
}

DualCANTalon::~DualCANTalon() {
	delete mAMotor;
	delete mBMotor;
}

void DualCANTalon::PIDWrite(float output) {
	Set(output);
}

void DualCANTalon::Set(float speed) {
	mAMotor->Set(mAInverted ? speed * -1 : speed);
	mBMotor->Set(mBInverted ? speed * -1 : speed);
}

float DualCANTalon::GetOutputCurrent() {
	float outputCurrentA = mAMotor->GetOutputCurrent();
	float outputCurrentB = mBMotor->GetOutputCurrent();

	float averageCurrent = (outputCurrentA + outputCurrentB) / 2;

	return averageCurrent;
}

float DualCANTalon::GetOutputVoltage() {
	float outputVoltageA = mAMotor->GetOutputVoltage();
	float outputVoltageB = mBMotor->GetOutputVoltage();

	float averageVoltage = (outputVoltageA + outputVoltageB) / 2;

	return averageVoltage;
}

float DualCANTalon::Get() {
	return mAMotor->Get();
}

CANTalon* DualCANTalon::GetTalonA() {
	return mAMotor;
}

void DualCANTalon::SetRamp(float value) {
	mAMotor->SetVoltageRampRate(value);
	mBMotor->SetVoltageRampRate(value);
}

CANTalon* DualCANTalon::GetTalonB() {
	return mBMotor;
}
