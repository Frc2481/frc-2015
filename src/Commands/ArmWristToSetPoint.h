#ifndef ArmWristToSetPoint_H
#define ArmWristToSetPoint_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmWristToSetPoint: public CommandBase
{
private:
	double mSetPoint;
public:
	ArmWristToSetPoint(double setpoint)
		: mSetPoint(setpoint){
	}
	void Initialize() {
		arm->SetWristLinked(false);
		arm->SetWristPosition(mSetPoint);
	}
	void Execute() {}
	bool IsFinished() {
		return arm->IsWristOnTarget();
	}
	void End() {
		arm->StopPivotWrist();
	}
	void Interrupted() {
		End();
	}
};

#endif
