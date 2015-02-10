#ifndef ARM_H
#define ARM_H

#include "WPILib.h"
#include "Commands/Subsystem.h"
#include "Components/ContinuousEncoder.h"
#include "PIDController2481.h"

class Arm: public Subsystem {
private:
	ContinuousEncoder* mShoulderEncoder;
	ContinuousEncoder* mWristEncoder;
	Solenoid* mArmExtention;
	Solenoid* mGripper;
	CANTalon* mPivotShoulderTalon;
	CANTalon* mPivotWristTalon;
	PIDController2481* mPIDShoulder;
	PIDController2481* mPIDWrist;
	float mWristOffset;

public:
	Arm(int armExtentionID, int gripperID, uint32_t shoulderEncoderID,
		uint32_t wristEncoderID, int shoulderTalonID, int gripperTalonID);
	void PeriodicUpdate();
	void SetWristOffset(float wristOffset);
	void SetPivotArmAbs(float position);
	void SetPivotArmRelative(float position);
	void StopPivotArm();
	void CloseGripper();
	void OpenGripper();
	void ExtendArm();
	bool IsGripper();
	bool IsExtended();
	void RetractArm();
	bool IsArmOnTarget();
	float GetPivotPos();
	float GetRawShoulderAngle();
	float GetRawWristAngle();
	void SetShoulderEncoderOffset(float shoulderOffset);
	void SetWristEncoderOffset(float wristOffset);

};


#endif
