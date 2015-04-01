/*
 * PController.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: Team2481
 */

#include "PController.h"
#include <cmath>
#include "SwerveModule.h"

PController::PController(PIDSource* userInput, PIDOutput* userOutput, float pValue, float iValue, float dValue) :
			input(userInput), 
			output(userOutput), 
			p(pValue),
			i(iValue),
			d(dValue),
			totalError(0),
			prevError(0),
			prevFeedback(std::nanf("")),
			tolerance(0),
			inputRangeUpper(0),
			inputRangeLower(5),
			inputRange(5),
			outputRangeUpper(1),
			outputRangeLower(-1),
			enabled(true),
			onTarget(false),
			pidOutput(0),
			setPoint(0),
			mContinuous(false),
			mBrake(false),
			mInverted(false),
			mStallCounter(0),
			mStallDetection(false),
			mStalled(false),
			pSemaphore(initializeMutexNormal()),
			pUpdate(new Notifier(PController::UpdateController, this)){
	pUpdate->StartPeriodic(.004);
}

PController::~PController() {
	takeMutex(pSemaphore);
	deleteMutex(pSemaphore);
	delete pUpdate;
	
}
void PController::SetP(float pValue){
	CRITICAL_REGION(pSemaphore) {
		p = pValue;
	}
	END_REGION;
}

float PController::GetP(){
	
	return p;
}

void PController::SetI(float iValue){
	CRITICAL_REGION(pSemaphore) {
		i = iValue;
	}
	END_REGION;
}

float PController::GetI(){
	
	return i;
}

void PController::SetD(float dValue){
	CRITICAL_REGION(pSemaphore){
		d = dValue;
	}
	END_REGION;
}

float PController::GetD(){
	return d;
}

void PController::SetTolerance(float userTolerance){
	tolerance = userTolerance;
}
void PController::SetSetpoint(float setPoint){
	CRITICAL_REGION(pSemaphore) {
		this->setPoint = setPoint;
	}
	END_REGION;
}

void PController::UpdateController(void* controller) {
	PController* control = (PController*) controller;
	control->Update();
}
void PController::Update() {
	float setPoint;
	float tolerance;
	float inputRange;
	bool onTarget = false;
	bool enabled;
	
	CRITICAL_REGION(pSemaphore) {
		setPoint = this->setPoint;
		tolerance = this->tolerance;
		inputRange = this->inputRange;
		enabled = this->enabled;

		if(enabled){
			float feedback = input->PIDGet();
			float error = setPoint - feedback;
			float correctedError = error;

			if (mContinuous){
				if (error < -inputRange / 2){
					onTarget = false;
					correctedError = error + inputRange;
				}
	
				else if(error  > inputRange / 2) {
					onTarget = false;
					correctedError = error - inputRange;
				}
				else {
					onTarget = false;
					correctedError = error;
				}
			}
			if (fabs(error) < tolerance){
				if (mBrake){
					correctedError = error;
				}
				else {
					correctedError = 0;
				}
				onTarget = true;
			}

			if(i > 0.0)
			{
				double potIGain = (totalError + correctedError) * i;
				if (potIGain < outputRangeUpper)
				{
					if(potIGain > outputRangeLower)
						totalError += correctedError;
					else
						totalError = outputRangeLower/i;
				}
				else
				{
					totalError = outputRangeUpper/i;
				}
			}

			pidOutput = -correctedError * p + d*(correctedError - prevError) + i*totalError;

			if (pidOutput > outputRangeUpper){
				pidOutput = outputRangeUpper;
			}
			else if (pidOutput < outputRangeLower){
				pidOutput = outputRangeLower;
			}
			if (mInverted) {
				pidOutput *= -1;
			}
			output->PIDWrite(-pidOutput);

			if (mStallDetection){
				if (fabs(pidOutput) > 0) {
					if (feedback > 300) {	//Hack for shoulder.
						feedback = 0;
					}
					float delta = fabs(feedback - prevFeedback);
					if (delta < 1) {
						mStallCounter++;
						mStallCounter = std::min(mStallCounter, 30);
					} else {
						mStallCounter = 0;
						prevFeedback = feedback;
					}
					if (mStallCounter >= 30) {
						mStalled = true;
					}
				} else {
					mStallCounter = 0;
					prevFeedback = feedback;
				}
			}

			if (mStalled){
				enabled = false;
			}

			prevError = correctedError;

		}
		this->enabled = enabled;
		this->onTarget = onTarget;
	}
	END_REGION;
}

void PController::SetInputRange(float lower, float upper){
	CRITICAL_REGION(pSemaphore) {
		inputRangeUpper = upper;
		inputRangeLower = lower;
		inputRange = inputRangeUpper - inputRangeLower;
	}
	END_REGION;
}

void PController::SetOutputRange(float lower, float upper){
	CRITICAL_REGION(pSemaphore) {
		outputRangeUpper = upper;
		outputRangeLower = lower;
	}
	END_REGION;
}

void PController::Enable(){
	CRITICAL_REGION(pSemaphore) {
		enabled = true;
	}
	END_REGION;

	ResetStalled();
}

void PController::Disable(){
	CRITICAL_REGION(pSemaphore) {
		enabled = false;
		output->PIDWrite(0);
	}
	END_REGION;

}

bool PController::IsEnabled(){
	return enabled;
}

bool PController::OnTarget(){
	return onTarget;
}
float PController::GetSetPoint(){
	return setPoint;
}

void PController::SetContinuous(bool continuous) {
	mContinuous = continuous;
}

void PController::SetBrakeMode(bool brake) {
	mBrake = brake;
}

void PController::Invert() {
	mInverted = true;
}

void PController::SetStallDetect(bool shouldStallDetect) {
	CRITICAL_REGION(pSemaphore){
		mStallDetection = shouldStallDetect;
	}
	END_REGION;
}

bool PController::GetStallDetect() {
	bool b;
	CRITICAL_REGION(pSemaphore){
		b = mStallDetection;
	}
	END_REGION;

	return b;
}

void PController::ResetStalled() {
	CRITICAL_REGION (pSemaphore){
		mHistory.reset();
		mStalled = false;
		prevFeedback = std::nanf("");
	}
	END_REGION;
}

bool PController::GetStalled() {
	bool b;
	CRITICAL_REGION(pSemaphore){
		b = mStalled;
	}
	END_REGION;

	return b;
}
