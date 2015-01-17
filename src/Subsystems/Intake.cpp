#include "Intake.h"
#include "../RobotMap.h"
#include "RobotParameters.h"



Intake::Intake(int leftCANID, int rightCANID):
	Subsystem("Intake"),
	mRightMotor(new CANTalon(rightCANID)),
	mLeftMotor(new CANTalon(leftCANID)) {

}

void Intake::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Intake::TurnOn() {
	mRightMotor->Set(INTAKE_FORWARD_SPEED);
	mLeftMotor->Set(INTAKE_FORWARD_SPEED);
	mState = On;
}

void Intake::TurnOff() {
	mRightMotor->Set(0.0f);
	mLeftMotor->Set(0.0f);
	mState = Off;
}

void Intake::TurnOnReverse() {
	mRightMotor->Set(INTAKE_REVERSE_SPEED);
	mLeftMotor->Set(INTAKE_REVERSE_SPEED);
	mState = Reverse;
}

void Intake::RotateCW() {
	mRightMotor->Set(INTAKE_FORWARD_SPEED);
	mLeftMotor->Set(INTAKE_REVERSE_SPEED * INTAKE_TRIM);
	mState = CW;
}

void Intake::RotateCCW() {
	mRightMotor->Set(INTAKE_REVERSE_SPEED * INTAKE_TRIM);
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
		mRightMotor->Set(INTAKE_REVERSE_SPEED);
		mLeftMotor->Set(INTAKE_FORWARD_SPEED * trim);
	}
	if (xValue >0.2){
		trim = (((xValue - 0.2f) * 2.0f) / 0.8f) - 1.0f;
		mRightMotor->Set(INTAKE_FORWARD_SPEED * trim);
		mLeftMotor->Set(INTAKE_REVERSE_SPEED);
	}
	else{
		mRightMotor->Set(INTAKE_REVERSE_SPEED);
		mLeftMotor->Set(INTAKE_REVERSE_SPEED);
	}
}

void Intake::PeriodicUpdate(){
#ifdef DEBUGGING
	SmartDashboard::PutNumber("getLeftMotorSpeed", mLeftMotor->Get());
	SmartDashboard::PutNumber("getRightMotorSpeed", mRightMotor->Get());
#endif
}


