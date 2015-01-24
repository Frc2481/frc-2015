/*
 * Lift2481.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: Team2481
 */

#include "Lift2481.h"

Lift2481::Lift2481(int motor, uint32_t encoderA, uint32_t encoderB, float P,
		float I, float D, uint32_t bottomLimit) {
	mMotor = new CANTalon(motor);
	mEncoder = new Encoder(encoderA, encoderB);
	mPIDController = new PIDController(P, I, D, mEncoder, mMotor);
	mBottomLimit = new DigitalInput(bottomLimit);

	mPIDController->SetAbsoluteTolerance(20.0f);
	mPIDController->SetInputRange(0, 9000);

	//Reset();            //remove for testing
	mState = NORMAL;
}

Lift2481::~Lift2481() {
	delete mMotor;
	delete mEncoder;
	delete mPIDController;
	delete mBottomLimit;
}

void Lift2481::PeriodicUpdate() {
	if (!mBottomLimit->Get()){
		if (mState == RESETTING){
			mMotor->Set(0);
		}
		mState = NORMAL;
		mEncoder->Reset();
	}
}

float Lift2481::GetCurrentPostion() {
	if (mState == RESETTING){
		return -1.0f;
	}
	else if(mState == FEEDBACK_DISABLE){
		return mPIDController->GetSetpoint();
	}
	return mEncoder->Get();
}

float Lift2481::GetDesiredPostion() {
	return mPIDController->GetSetpoint();
}

void Lift2481::SetDesiredPostion(float pos) {
	mPIDController->SetSetpoint(pos);

	if(mState == NORMAL){
		mPIDController->Enable();
	}
}

bool Lift2481::OnTarget() {
	if (mState == FEEDBACK_DISABLE){
		return true;
	}
	return mPIDController->OnTarget();
}

void Lift2481::Reset() {
	if (mState != FEEDBACK_DISABLE){
		mState = RESETTING;
		mPIDController->Disable();
		mMotor->Set(-1);
	}
}

void Lift2481::Stop(){
	mPIDController->Disable();
	mMotor->Set(0);
}

bool Lift2481::IsResetting(){
	return mState == RESETTING;
}

Lift2481::LiftState Lift2481::GetLiftState() {
	return mState;
}

PIDController* Lift2481::GetController(){
	return mPIDController;
}

void Lift2481::SetFeedbackState(bool state) {
	if (state){
		mState = NORMAL;
	}
	else{
		mState = FEEDBACK_DISABLE;
		mPIDController->Disable();
	}
}

