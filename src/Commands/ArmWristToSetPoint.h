#ifndef ArmWristToSetPoint_H
#define ArmWristToSetPoint_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmWristToSetPoint: public CommandBase
{
protected:
	double mSetPoint;
	bool mDone;
public:
	ArmWristToSetPoint(double setpoint)
		: mSetPoint(setpoint){
		Requires(arm);
	}
	virtual void Initialize() {
		 mDone = false;
		arm->SetWristLinked(false);
		arm->SetWristPosition(mSetPoint);
	}
	void Execute() {}
	bool IsFinished() {
		return arm->IsWristOnTarget() || mDone;
	}
	void End() {
		arm->StopPivotWrist();
	}
	void Interrupted() {
		End();
	}
};

class ArmWristToTippedOverCan : public ArmWristToSetPoint {
public:
	ArmWristToTippedOverCan(double setpoint) : ArmWristToSetPoint(setpoint) {
	}
	void Initialize() {

		if (arm->GetShoulderAngle() < SHOULDER_TIPPED_OVER_CAN){
			arm->SetWristLinked(false);
			arm->SetWristPosition(mSetPoint, true);

			mDone = arm->GetWristAngle() > 260;
		}
		else {
			mDone = true;
		}
	}
};
#endif
