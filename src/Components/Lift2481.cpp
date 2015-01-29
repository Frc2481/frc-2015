/*
 * Lift2481.cpp
 *
 *  Created on: Jan 10, 2015
 *      Author: Team2481
 */

#include "Lift2481.h"
#include "RobotParameters.h"

Lift2481::Lift2481(int motor, uint32_t encoderA, uint32_t encoderB, float P,
		float I, float D, uint32_t bottomLimit, uint32_t topLimit) {
	mEncoder = new Encoder(encoderA, encoderB);
	mBottomLimit = new DigitalInput(bottomLimit);
	mTopLimit = new DigitalInput(topLimit);
	mPIDOutput = new LiftPIDOutput2481(motor, mBottomLimit, mTopLimit);
	mPIDController = new PIDController2481(P, I, D, mEncoder, mPIDOutput, .01);

	mPIDController->SetAbsoluteTolerance(200.0f);
	mPIDController->SetInputRange(0, STACKER_POSITION_UP);

	//Reset();            //remove for testing
	mState = NORMAL;
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
	//mPIDController->SetPID(mPIDController->GetP() ,mPIDController->GetI() *.01,mPIDController->GetD());

	if(mState == NORMAL){
		mPIDController->Reset();
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
	mEncoder->Reset();
	//	if (mState != FEEDBACK_DISABLE){
//		mState = RESETTING;
//		mPIDController->Disable();
//		mPIDOutput->Set(-.5);
	}
//}

void Lift2481::Stop(){
	//mPIDController->Disable();
	//mPIDOutput->Set(0);
}

bool Lift2481::IsResetting(){
	return mState == RESETTING;
}

Lift2481::LiftState Lift2481::GetLiftState() {
	return mState;
}

PIDController2481* Lift2481::GetController(){
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

void Lift2481::SetP(float p) {
	mPIDController->SetPID(p, mPIDController->GetI(), mPIDController->GetD());
}

void Lift2481::SetI(float i) {
	mPIDController->SetPID(mPIDController->GetP(), i, mPIDController->GetD());
}

void Lift2481::SetInverted(bool invert) {
	mPIDOutput->InvertMotor(invert);
}

LiftPIDOutput2481::LiftPIDOutput2481(int motor, DigitalInput* bot,
		DigitalInput* top) {
	mMotor = new CANTalon(motor);
	mMotor->ConfigNeutralMode(CANTalon::kNeutralMode_Brake);
	mBottomLimit = bot;
	mTopLimit = top;
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


