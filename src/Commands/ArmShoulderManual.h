#ifndef ArmShoulderManual_H
#define ArmShoulderManual_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmShoulderManual: public CommandBase
{
private:
	double mSetPoint;
public:
	ArmShoulderManual(double setpoint)
		: mSetPoint(setpoint){
	}
	void Initialize(){
		arm->SetShoulderManual(mSetPoint);
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		arm->StopPivotArm();
	}
	void Interrupted(){
		End();
	}
};

#endif
