#ifndef ARM_H
#define ARM_H

#include "WPILib.h"
#include "Commands/Subsystem.h"

class Arm: public Subsystem {
private:
	Solenoid* mArmExtention;
	Solenoid* mGripper;
	CANTalon* mPivotArmRightTalon;
	CANTalon* mPivotArmLeftTalon;
	CANTalon* mPivotGripperTalon;
	float mArmLeftPosition;
	float mArmPosition;
	float mGripperPosition;
	bool mLocked;

public:
	Arm(int armExtentionID,int gripperID,int pivotRightTalonID,
		int pivotLeftTalonID,int gripperTalonID);
	void SetPivotArmAbs(float position);
	void SetPivotArmRelative(float position);
	void StopPivotArm();
	void SetWristAbs(float position);
	void CloseGripper();
	void OpenGripper();
	void ExtendArm();
	void RetractArm();
	bool IsLiftOnTarget();
	bool IsLocked();
	float GetPivotPos();
	void ToggleLock();

};


#endif
