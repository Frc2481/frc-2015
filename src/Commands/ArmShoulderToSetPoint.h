#ifndef ArmShoulderToSetPoint_H
#define ArmShoulderToSetPoint_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmShoulderToSetPoint: public CommandBase
{
protected:
	double mSetPoint;
	bool mDone;
	bool mLinked;
public:
	ArmShoulderToSetPoint(double setpoint, bool linked = true)
		: mSetPoint(setpoint),
		  mLinked(linked){
	}
	virtual void Initialize(){
		mDone = false;
		if (mLinked){
			arm->SetWristLinked(true);
		}
		arm->SetPivotArmAbs(mSetPoint);
	}
	void Execute(){
		if(false){   //TODO: check if motor is stalled

		}
	}
	bool IsFinished(){
		return arm->IsArmOnTarget() || mDone;
	}
	void End(){
		if (mLinked){
			arm->SetWristLinked(false);
		}
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
