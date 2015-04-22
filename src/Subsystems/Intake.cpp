#include "Intake.h"
#include "../RobotMap.h"
#include <iostream>
#include "../RobotParameters.h"



Intake::Intake() : Subsystem("Intake"),
	mRightMotor(new CANTalon(INTAKE_RIGHT)),
	mLeftMotor(new CANTalon(INTAKE_LEFT)),
	mIntakeLimit(new DigitalInput(INTAKE_CONTAIN_LIMIT)){

	mRightMotor->ConfigNeutralMode(CANTalon::kNeutralMode_Coast);
	mLeftMotor->ConfigNeutralMode(CANTalon::kNeutralMode_Coast);
}

void Intake::InitDefaultCommand(){}

void Intake::TurnOn(double speed) {
	mRightMotor->Set(speed);
	mLeftMotor->Set(-speed);
	mState = On;
}

void Intake::TurnOff() {
	mRightMotor->Set(0.0f);
	mLeftMotor->Set(0.0f);
	mState = Off;
}

void Intake::TurnOnReverse(double speed) {
	mRightMotor->Set(speed);
	mLeftMotor->Set(-speed);
	mState = Reverse;
}

void Intake::TurnOnLeftReverse() {
	mLeftMotor->Set(-INTAKE_REVERSE_SPEED);
	mState = Reverse;
}

void Intake::RotateCW() {
	mRightMotor->Set(-INTAKE_FORWARD_SPEED);
	mLeftMotor->Set(INTAKE_REVERSE_SPEED * INTAKE_TRIM);
	mState = CW;
}

void Intake::RotateCCW() {
	mRightMotor->Set(-INTAKE_REVERSE_SPEED * INTAKE_TRIM);
	mLeftMotor->Set(INTAKE_FORWARD_SPEED);
	mState = CCW;
}

bool Intake::IsOn() {
	return mState == On;
}

bool Intake::IsOff() {
	return mState == Off;
}

void Intake::IntakeManual(float xValue){

	float trim;

	if (xValue < -0.2){
		trim = (((xValue + 1.0f) * -2.0f) / 0.8f) + 1.0f;
		mRightMotor->Set(-INTAKE_REVERSE_SPEED);
		mLeftMotor->Set(-INTAKE_REVERSE_SPEED * trim);
	}
	else if (xValue > 0.2){
		trim = (((xValue - 0.2f) * 2.0f) / 0.8f) - 1.0f;
		mRightMotor->Set(INTAKE_REVERSE_SPEED * trim);
		mLeftMotor->Set(INTAKE_REVERSE_SPEED);
	}
	else{
		mRightMotor->Set(-INTAKE_REVERSE_SPEED);
		mLeftMotor->Set(INTAKE_REVERSE_SPEED);
	}
}

void Intake::PeriodicUpdate(){
#ifdef DEBUGGING
//	SmartDashboard::PutNumber("IntakeLeftMotorSpeed", mLeftMotor->Get());
//	SmartDashboard::PutNumber("IntakeRightMotorSpeed", mRightMotor->Get());
	SmartDashboard::PutBoolean("Contain Limit", mIntakeLimit->Get());
#endif
}

bool Intake::IsContained() {
	return !mIntakeLimit->Get();
}
