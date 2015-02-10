/*
 * PController.cpp
 *
 *  Created on: Jan 17, 2014
 *      Author: Team2481
 */

#include "PController.h"
#include <cmath>
#include "SwerveModule.h"

PController::PController(PIDSource* userInput, PIDOutput* userOutput, float pValue, float iValue) :
			input(userInput), 
			output(userOutput), 
			p(pValue),
			i(iValue),
			totalError(0),
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
			pSemaphore(initializeMutexNormal()),
			pUpdate(new Notifier(PController::UpdateController, this)){
	pUpdate->StartPeriodic(.004);
}

PController::~PController() {
	takeMutex(pSemaphore);
	deleteMutex(pSemaphore);
	delete pUpdate;
	// TODO Auto-generated destructor stub
	
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
	bool onTarget;
	bool enabled;
	
	CRITICAL_REGION(pSemaphore) {
		setPoint = this->setPoint;
		tolerance = this->tolerance;
		inputRange = this->inputRange;
		enabled = this->enabled;
	}
	END_REGION;
	
	if(enabled){
		float feedback = input->PIDGet();
		float error = setPoint - feedback;
		float correctedError = 0;
		if (error < 0){
			error +=360;
		}
		
		if (fabs(error) < tolerance){
			correctedError = 0;
			onTarget = true;
		}
		else if (error < -inputRange / 2){
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

		/*
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
	*/
		pidOutput = -correctedError * p;// + i*totalError;
		
		if (pidOutput > outputRangeUpper){
			pidOutput = outputRangeUpper;
		}
		else if (pidOutput < outputRangeLower){
			pidOutput = outputRangeLower;
		}
		output->PIDWrite(-pidOutput);
	}
	else {
		output->PIDWrite(0);
	}
	
	CRITICAL_REGION(pSemaphore) {
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
}

void PController::Disable(){
	CRITICAL_REGION(pSemaphore) {
		enabled = false;
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
