/*
 * Lift2481.h
 *
 *  Created on: Jan 10, 2015
 *      Author: Team2481
 */

#ifndef SRC_COMPONENTS_LIFT2481_H_
#define SRC_COMPONENTS_LIFT2481_H_

#include "../PIDController2481.h"
#include "WPILib.h"

class LiftPIDOutput2481 : public PIDOutput {
private:
	CANTalon* mMotor;
	DigitalInput* mBottomLimit;
	DigitalInput* mTopLimit;
	bool mInverted;
public:
	LiftPIDOutput2481(int motor, DigitalInput* bot, DigitalInput* top);
	virtual ~LiftPIDOutput2481();
	void PIDWrite(float output);
	void Set(float output);
	void InvertMotor(bool invert);
};

class Lift2481 {
public:
	enum LiftState {
		NORMAL,
		RESETTING,
		FEEDBACK_DISABLE,
	};
private:
	Encoder* mEncoder;
	LiftPIDOutput2481* mPIDOutput;
	PIDController2481* mPIDController;
	DigitalInput* mBottomLimit;
	DigitalInput* mTopLimit;
	LiftState mState;
public:

	Lift2481(int motor, uint32_t encoderA, uint32_t encoderB, float P, float I, float D, uint32_t bottomLimit, uint32_t topLimit);
	virtual ~Lift2481();
	void PeriodicUpdate();
	float GetCurrentPostion();
	float GetDesiredPostion();
	void SetDesiredPostion(float);
	bool OnTarget();
	void Reset();
	void Stop();
	bool IsResetting();
	void SetFeedbackState(bool state);
	LiftState GetLiftState();
	PIDController2481* GetController();
	void SetP(float p);
	void SetI(float i);
	void SetInverted(bool invert);
};

#endif /* SRC_COMPONENTS_LIFT2481_H_ */
