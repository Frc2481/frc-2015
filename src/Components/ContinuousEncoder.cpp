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
	
	// TODO Auto-generated constructor stub
	sum = 0;
	index = 0;
	memset(prevEncoderValues, 0, sizeof(float) * 5);
}

ContinuousEncoder::~ContinuousEncoder() {
	delete mEncoder;
}
double ContinuousEncoder::PIDGet(){
	sum -= prevEncoderValues[index];
	prevEncoderValues[index] = GetAngle();
	sum += prevEncoderValues[index];
	index = ++index % 5;
	return sum / 5;
}
	
double ContinuousEncoder::GetAngle() {
	double t = GetRawAngle() - mOffset;
	while (t < 0)
		t += 360;
	return t;
}

double ContinuousEncoder::GetRawAngle() {
	return ((mEncoder->GetAverageVoltage() - 0.015) / 4.972) * 360;
}

float ContinuousEncoder::GetOffset() const
{
    return mOffset;
}

void ContinuousEncoder::SetOffset(float mOffset)
{
    this->mOffset = mOffset;
}

float ContinuousEncoder::getVoltage() {
	return mEncoder->GetAverageVoltage();
}
