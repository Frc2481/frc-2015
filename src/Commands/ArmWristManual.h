#ifndef ArmWristToManual_H
#define ArmWristToManual_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmWristManual: public CommandBase
{
private:
	double mSetPoint;
public:
	ArmWristManual(double setpoint)
		: mSetPoint(setpoint){
	}
	void Initialize() {
		arm->SetWristManual(mSetPoint);
	}
	void Execute() {}
	bool IsFinished() {
		return arm->GetStalled();
	}
	void End() {
		arm->StopPivotWrist();
	}
	void Interrupted() {
		End();
	}
};

#endif
