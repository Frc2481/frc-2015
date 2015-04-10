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
#include "DualCANTalon.h"
#include "RollingAccumulator.h"
#include "LiftPIDOutput2481.h"
#include "DigitalInputTrigger.h"

class Lift2481 {
public:
	enum LiftState {
		NORMAL,
		RESETTING,
	};
	enum BrakeState {
		STATIC,
		APPLYING,
		RELEASING,
	};
private:
	Encoder* mEncoder;
	LiftPIDOutput2481* mPIDOutput;
	PIDController2481* mPIDController;
	DigitalInput* mBottomLimit;
	DigitalInput* mTopLimit;
	DigitalInputTrigger* mImputTrigger;
	Solenoid* mBrake;
	LiftState mState;
	BrakeState mBrakeState;
	RollingAccumulator <float, 50> mCurrentAverager;
	RollingAccumulator <float, 50> mVoltageAverager;
	int mMotorOnCount;
	int mMotorOffCount;
	int mManualOffCount;
public:

	Lift2481(int motor, uint32_t encoderA, uint32_t encoderB, float P, float I, float D, uint32_t bottomLimit, uint32_t topLimit, int brake);
	virtual ~Lift2481();
	void PeriodicUpdate();
	float GetCurrentPostion();
	float GetDesiredPostion();
	float GetAverageCurrent();
	float GetAverageVoltage();
	void SetDesiredPostion(float);
	bool OnTarget();
	void Reset();
	void Disable(bool motor = true, bool brake = true);
	void Enable(bool motor = true);
	bool IsResetting();
	LiftState GetLiftState();
	PIDController2481* GetController();
	void SetP(float p);
	void SetI(float i);
	void SetD(float d);
	void SetInverted(bool invert);
	void Set(float speed);
	float GetSpeed();
	float GetCurrentStdDev();
	bool IsTopLimit();
	bool IsBottomLimit();
};

#endif /* SRC_COMPONENTS_LIFT2481_H_ */
