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
	DualCANTalon(int motorA, int motorB, bool AInvert, bool BInvert);
	virtual ~DualCANTalon();
	void PIDWrite(float output);
	void Set(float speed);
	float GetOutputCurrent();
	float GetOutputVoltage();
	float Get();
};

#endif /* SRC_COMPONENTS_DUALCANTALON_H_ */
