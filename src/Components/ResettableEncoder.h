
// * ResettableEncoder.h
// *
// *  Created on: Feb 15, 2015
// *      Author: Team2481
// */

#ifndef SRC_COMPONENTS_RESETTABLEENCODER_H_
#define SRC_COMPONENTS_RESETTABLEENCODER_H_

#include<Encoder.h>
#include<CounterBase.h>

class ResettableEncoder : public PIDSource {
private:
	int mOffset;
	Encoder* enc;
public:
	ResettableEncoder(uint32_t aChannel, uint32_t bChannel, bool reverseDirection = false,
			CounterBase::EncodingType encodingType = CounterBase::k4X);
	virtual ~ResettableEncoder();
	void Reset(double desiredValue = 0.0);
	double PIDGet();
};

#endif /* SRC_COMPONENTS_RESETTABLEENCODER_H_ */
