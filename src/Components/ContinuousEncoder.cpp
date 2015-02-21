/*
 * ContinuousEncoder.cpp
 *
 *  Created on: Jan 16, 2014
 *      Author: Team2481
 */

#include "ContinuousEncoder.h"

ContinuousEncoder::ContinuousEncoder(uint32_t encoderChannel)
		:	mEncoder(new AnalogInput(encoderChannel)),
		 	mOffset(0) {
}

ContinuousEncoder::~ContinuousEncoder() {
	delete mEncoder;
}
double ContinuousEncoder::PIDGet(){
	return GetAngle();
}
	
double ContinuousEncoder::GetAngle() {
	double t = GetRawAngle() - mOffset;
	while (t < 0)
		t += 360;
	return t;
}

double ContinuousEncoder::GetRawAngle() {
	return ((getVoltage()- 0.015) / (4.987 - .015)) * 360;
}

float ContinuousEncoder::GetOffset() const{
    return mOffset;
}

void
ContinuousEncoder::SetOffset(float mOffset){
    this->mOffset = mOffset;
}

float ContinuousEncoder::getVoltage() {
	return (mEncoder->GetVoltage() / ControllerPower::GetVoltage5V()) * 5;
}

float ContinuousEncoder::GetRawVoltage() {
	return mEncoder->GetVoltage();
}

