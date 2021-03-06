/*
 * ContinuousEncoder.h
 *
 *  Created on: Jan 16, 2014
 *      Author: Team2481
 */

#ifndef CONTINUOUSENCODER_H_
#define CONTINUOUSENCODER_H_
#include "WPILib.h"

class ContinuousEncoder: public PIDSource {
private:
	AnalogInput *mEncoder;
	float mOffset;
	
public:
	ContinuousEncoder(uint32_t encoderChannel);
	virtual ~ContinuousEncoder();
	virtual double PIDGet();
	double GetAngle();
	double GetRawAngle();
	float getVoltage();
    float GetOffset() const;
    void SetOffset(float mOffset);
    float GetRawVoltage();
	
};

#endif /* CONTINUOUSENCODER_H_ */
