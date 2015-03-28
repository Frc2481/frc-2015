/*
 * Lift2481.h
 *
 *  Created on: Jan 10, 2015
 *      Author: Team2481
 */

#ifndef SRC_COMPONENTS_LIFTPIDOUTPUT2481_H_
#define SRC_COMPONENTS_LIFTPIDOUTPUT2481_H_

#include "WPILib.h"
#include "DualCANTalon.h"

class LiftPIDOutput2481 : public PIDOutput {
private:
	DualCANTalon* mMotor;
	DigitalInput* mBottomLimit;
	DigitalInput* mTopLimit;
	bool mInverted;
public:
	LiftPIDOutput2481(int motor, DigitalInput* bot, DigitalInput* top);
	virtual ~LiftPIDOutput2481();
	void PIDWrite(float output);
	void Set(float output);
	void InvertMotor(bool invert);
	float GetMotorCurrent();
	float Get();
};

#endif /* SRC_COMPONENTS_LIFTPIDOUTPUT2481_H_ */
