#ifndef ArmShoulderToSetPoint_H
#define ArmShoulderToSetPoint_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmShoulderToSetPoint: public CommandBase
{
protected:
	double mSetPoint;
	bool mDone;
public:
	ArmShoulderToSetPoint(double setpoint)
		: CommandBase("ArmShoulderToSetPoint"),
			mSetPoint(setpoint) {
	}
	virtual void Initialize(){
		mDone = false;
		arm->SetWristLinked(true);
		arm->SetPivotArmAbs(mSetPoint);
	}
	void Execute(){}
	bool IsFinished(){
		return arm->IsArmOnTarget() || mDone;
	}
	void End(){
		arm->SetWristLinked(false);
		//if (mSetPoint != ARM_STEP_HEIGHT) {
			arm->StopPivotArm();
		//}
	}
	void Interrupted(){
		End();
	}
};

class ArmShoulderToFloor : public ArmShoulderToSetPoint {
public:
	ArmShoulderToFloor(double setpoint)
		: ArmShoulderToSetPoint(setpoint){
	}
	void Initialize(){
		if (arm->GetWristAngle() > 200
				&& arm->GetShoulderAngle() > SHOULDER_TIPPED_OVER_CAN){
			mDone = true;
		}
		else {
			ArmShoulderToSetPoint::Initialize();
		}
	}
};

class ArmShoulderToFloorTippedOverCan : public ArmShoulderToSetPoint {
public:
	ArmShoulderToFloorTippedOverCan(double setpoint)
		: ArmShoulderToSetPoint(setpoint){
	}
	void Initialize(){
		if (arm->GetShoulderAngle() > SHOULDER_TIPPED_OVER_CAN){
			mDone = true;
		}
		else {
			ArmShoulderToSetPoint::Initialize();
		}
	}
};

#endif
