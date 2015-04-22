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
#include "RobotParameters.h"

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
	Intake();
	void InitDefaultCommand();
	void TurnOn(double speed = INTAKE_FORWARD_SPEED);
	void TurnOff();
	void TurnOnReverse(double speed = INTAKE_REVERSE_SPEED);
	void TurnOnLeftReverse();
	void RotateCW();
	void RotateCCW();
	bool IsOn();
	bool IsOff();
	void IntakeManual(float xValue);
	void PeriodicUpdate();
	bool IsContained();

};

#endif
