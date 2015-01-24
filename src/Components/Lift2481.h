/*
 * Lift2481.h
 *
 *  Created on: Jan 10, 2015
 *      Author: Team2481
 */

#ifndef SRC_COMPONENTS_LIFT2481_H_
#define SRC_COMPONENTS_LIFT2481_H_

#include "WPILib.h"

class Lift2481 {
public:
	enum LiftState {
		NORMAL,
		RESETTING,
		FEEDBACK_DISABLE,
	};
private:
	CANTalon* mMotor;
	Encoder* mEncoder;
	PIDController* mPIDController;
	DigitalInput* mBottomLimit;
	LiftState mState;
public:

	Lift2481(int motor, uint32_t encoderA, uint32_t encoderB, float P, float I, float D, uint32_t bottomLimit);
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
	PIDController* GetController();
};

#endif /* SRC_COMPONENTS_LIFT2481_H_ */
