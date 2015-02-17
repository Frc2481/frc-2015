/*
 * ResettableEncoder.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: Team2481
 */

#include <Components/ResettableEncoder.h>
#include<Encoder.h>
#include<CounterBase.h>

ResettableEncoder::ResettableEncoder(uint32_t aChannel, uint32_t bChannel, bool reverseDirection,
		CounterBase::EncodingType encodingType) {
	// TODO Auto-generated constructor stub
	enc = new Encoder(aChannel, bChannel, reverseDirection, encodingType);
	mOffset = 0.0;
}

ResettableEncoder::~ResettableEncoder() {
	// TODO Auto-generated destructor stub
	delete enc;
}

void ResettableEncoder::Reset(double desiredValue) {
	enc->Reset();
	mOffset = desiredValue;
}

double ResettableEncoder::PIDGet() {
	return enc->GetDistance() + mOffset;
}

