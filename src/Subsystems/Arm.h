#ifndef ARM_H
#define ARM_H

#include "WPILib.h"
#include "Commands/Subsystem.h"
#include "Components/ContinuousEncoder.h"
#include "Components/PController.h"

class Arm: public Subsystem {
private:
	ContinuousEncoder* mShoulderEncoder;
	ContinuousEncoder* mWristEncoder;
	Solenoid* mArmExtention;
	Solenoid* mGripper;
	CANTalon* mPivotShoulderTalon;
	CANTalon* mPivotWristTalon;
	PController* mPIDShoulder;
	PController* mPIDWrist;
	int mWristOffset;
	bool mWristStalled;
	bool mWristLocked;

public:
	Arm();
	void PeriodicUpdate();
	void SetWristOffset(float wristOffset);
	void SetWristOffsetRelative(int offsetWrist);
	void SetPivotArmAbs(float position);
	void SetPivotArmRelative(float position);
	void SetWristLinked(bool linked);
	void StopPivotArm();
	void StopPivotWrist();
	void CloseGripper();
	void OpenGripper();
	void ExtendArm();
	bool IsGripper();
	bool IsExtended();
	void RetractArm();
	bool IsArmOnTarget();
	bool IsWristOnTarget();
//	float GetPivotPos();
	float GetRawShoulderAngle();
	float GetRawWristAngle();
	double GetParallel();
	bool GetStalled();
	void SetStalled(bool stalled);
	void SetShoulderEncoderOffset(float shoulderOffset);
	void SetWristEncoderOffset(float wristOffset);
	void SetWristPosition(double pos);
	void SetWristManual(double speed);
	void SetShoulderManual(double speed);
};


#endif
