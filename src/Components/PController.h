/*
 * PController.h
 *
 *  Created on: Jan 17, 2014
 *      Author: Team2481
 */

#ifndef PCONTROLLER_H_
#define PCONTROLLER_H_
#include "WPILib.h"
#include "RollingAccumulator.h"

class PController {
private:
	PIDSource* input;
	PIDOutput* output;
	RollingAccumulator <float, 50> mHistory;
	bool mStallDetection;
	bool mStalled;
	float p;
	float i;
	float d;
	float totalError;
	float prevError;
	float prevFeedback;
	float tolerance;
	float inputRangeUpper;
	float inputRangeLower;
	float inputRange;
	float outputRangeUpper;
	float outputRangeLower;
	bool enabled;
	bool onTarget;
	float pidOutput;
	float setPoint;
	bool mContinuous;
	bool mBrake;
	bool mInverted;
	MUTEX_ID pSemaphore;
	Notifier* pUpdate;
public:
	PController(PIDSource* userInput, PIDOutput* userOutput, float pValue, float iValue, float dValue = 0.0f);
	virtual ~PController();
	void SetP(float pValue);
	float GetP();
	void SetI(float iValue);
	float GetI();
	void SetD(float dValue);
	float GetD();
	void SetTolerance(float userTolerance);
	void SetSetpoint(float setPoint);
	void SetInputRange(float lower, float uper);
	void SetOutputRange(float lower, float upwer);
	void SetContinuous(bool continuous);
	void Enable();
	void Disable();
	bool IsEnabled();
	bool OnTarget();
	static void UpdateController(void* controller);
	void Update();
	float GetSetPoint();
	void SetBrakeMode(bool brake);
	void Invert();
	void SetStallDetect(bool shouldStallDetect);
	bool GetStallDetect();
	void ResetStalled();
	bool GetStalled();
};

#endif /* PCONTROLLER_H_ */
