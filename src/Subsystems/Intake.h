/*
 * Intake.h
 *
 *  Created on: Jan 16, 2015
 *      Author: thomasSpeciale
 */

#ifndef Intake_H
#define Intake_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Intake: public Subsystem
{

private:
	CANTalon* mRightMotor;
	CANTalon* mLeftMotor;
	DigitalInput* mIntakeLimit;
	enum IntakeState{
		Off,
		On,
		Reverse,
		CW,
		CCW
	} mState;

	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
public:
	Intake(int leftCANID,int rightCANID,int limitID);
	void InitDefaultCommand();
	void TurnOn();
	void TurnOff();
	void TurnOnReverse();
	void RotateCW();
	void RotateCCW();
	bool IsOn();
	bool IsOff();
	void IntakeManual(float xValue);
	void PeriodicUpdate();
	bool IsContained();

};

#endif
