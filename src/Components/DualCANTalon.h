/*
 * DualCANTalon.h
 *
 *  Created on: Jan 29, 2015
 *      Author: Team2481
 */

#ifndef SRC_COMPONENTS_DUALCANTALON_H_
#define SRC_COMPONENTS_DUALCANTALON_H_

#include "WPILib.h"

class DualCANTalon : public PIDOutput {
private:
	CANTalon* mAMotor;
	CANTalon* mBMotor;
	bool mAInverted;
	bool mBInverted;
public:
	DualCANTalon(int motorA, int motorB, bool AInvert, bool BInvert, bool ramp = false, bool motorBrake = true);
	virtual ~DualCANTalon();
	void PIDWrite(float output);
	void Set(float speed);
	void SetRamp(float value);
	float GetOutputCurrent();
	float GetOutputVoltage();
	float Get();
	CANTalon* GetTalonA();
	CANTalon* GetTalonB();
};

#endif /* SRC_COMPONENTS_DUALCANTALON_H_ */
