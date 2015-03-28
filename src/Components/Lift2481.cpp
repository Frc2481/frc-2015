/*
 * Lift2481.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: Team2481
 */

#include "Lift2481.h"
#include "RobotParameters.h"

Lift2481::Lift2481(int motor, uint32_t encoderA, uint32_t encoderB, float P,
		float I, float D, uint32_t bottomLimit, uint32_t topLimit, int brake) {
	mEncoder = new Encoder(encoderA, encoderB);
//	mEncoder->SetDistancePerPulse(1.0f / 578.0f);
	mBottomLimit = new DigitalInput(bottomLimit);
	mTopLimit = new DigitalInput(topLimit);
	mPIDOutput = new LiftPIDOutput2481(motor, mBottomLimit, mTopLimit);
	mPIDController = new PIDController2481(P, I, D, mEncoder, mPIDOutput, .01);
	mBrake = new Solenoid(brake);

	mMotorOffCount = mMotorOnCount = 0;

	mPIDController->SetAbsoluteTolerance(200.0f);
	mPIDController->SetInputRange(0, STACKER_POSITION_UP);

	//Reset();            //remove for testing
	mState = NORMAL;
	mBrakeState = STATIC;
}

Lift2481::~Lift2481() {
	delete mEncoder;
	delete mPIDController;
	delete mBottomLimit;
}

void Lift2481::PeriodicUpdate() {
//	if (mBottomLimit->Get()){
//		if (mState == RESETTING){
//			mPIDOutput->Set(0);
//		}
//		mState = NORMAL;
//		mEncoder->Reset();
//	}
	SmartDashboard::PutNumber("Brake State1", (int)mBrakeState);

	SmartDashboard::PutNumber("PIDGet Stacker", mEncoder->PIDGet());
	SmartDashboard::PutNumber("Stacker Speed", mPIDOutput->Get());

	if (mState == NORMAL) {

		//Turn the motor off if the brake has been applied for 4
		//iterations through the loop.
		if (mBrakeState == APPLYING) {
			mBrake->Set(false);
			mMotorOffCount++;
		}

		if (mMotorOffCount >= 1) {
			mPIDController->Disable();
			mBrakeState = STATIC;
		}

		//Turn the motor on if the brake has been removed for 4
		//iterations through the loop.
		if (mBrakeState == RELEASING) {
			mBrake->Set(true);
			mMotorOnCount++;
		}

		if (mMotorOnCount >= 3) {
			mPIDController->Enable();
			mBrakeState = STATIC;
		}
		if (mBrakeState == STATIC){
			mMotorOnCount = mMotorOffCount = 0;
		}
	}

	SmartDashboard::PutBoolean("Brake", mBrake->Get());

	mCurrentAverager.add(mPIDOutput->GetMotorCurrent());
}

float Lift2481::GetCurrentPostion() {
	if (mState == RESETTING){
		return -1.0f;
	}
	return mEncoder->Get();
}

float Lift2481::GetDesiredPostion() {
	return mPIDController->GetSetpoint();
}

void Lift2481::SetDesiredPostion(float pos) {
	mPIDController->SetSetpoint(pos);

	if(mState == NORMAL){
		mPIDController->Reset();
		mBrakeState = RELEASING; //PIDController is automatically enabled later.

	}
}

bool Lift2481::OnTarget() {
	return mPIDController->OnTarget();
}

void Lift2481::Reset() {
	mEncoder->Reset();
//		mState = RESETTING;
//		mPIDController->Disable();
//		mPIDOutput->Set(-.5);
	}
//}

bool Lift2481::IsResetting(){
	return mState == RESETTING;
}

Lift2481::LiftState Lift2481::GetLiftState() {
	return mState;
}

PIDController2481* Lift2481::GetController(){
	return mPIDController;
}

void Lift2481::SetP(float p) {
	mPIDController->SetPID(p, mPIDController->GetI(), mPIDController->GetD());
}

void Lift2481::SetI(float i) {
	mPIDController->SetPID(mPIDController->GetP(), i, mPIDController->GetD());
}

void Lift2481::SetInverted(bool invert) {
	mPIDOutput->InvertMotor(invert);
}

void Lift2481::Set(float speed) {
	if (mPIDController->IsEnabled()) {
		mPIDController->Disable();
		mBrake->Set(true);
	} else {
		mPIDOutput->Set(speed);
	}

}

float Lift2481::GetAverageCurrent() {
	return mCurrentAverager.avg();
}

void Lift2481::Disable(bool motor, bool brake) {
	if (motor && !brake){
		mPIDController->Disable();
		mBrakeState = STATIC;
	}
	else if (motor && brake){
		mBrakeState = APPLYING;
	}
	else {
		mBrake->Set(false);
		mBrakeState = STATIC;
	}
}
void Lift2481::Enable(bool motor){
	if (motor){
		mBrakeState = RELEASING;
	}
	else {
		mBrakeState = STATIC;
		mBrake->Set(true);
	}
}


float Lift2481::GetSpeed() {
	return mEncoder->GetRate();
}

float Lift2481::GetCurrentStdDev() {
	return mCurrentAverager.stddev();
}

bool Lift2481::IsTopLimit() {
	return mTopLimit->Get();
}

void Lift2481::SetD(float d) {
	mPIDController->SetPID(mPIDController->GetP(), mPIDController->GetI(), d);
}

float Lift2481::GetAverageVoltage() {
	return mVoltageAverager.avg();
}

bool Lift2481::IsBottomLimit() {
	return mBottomLimit->Get();
}
