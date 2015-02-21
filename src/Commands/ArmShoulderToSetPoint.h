#ifndef ArmShoulderToSetPoint_H
#define ArmShoulderToSetPoint_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmShoulderToSetPoint: public CommandBase
{
private:
	double mSetPoint;
public:
	ArmShoulderToSetPoint(double setpoint)
		: mSetPoint(setpoint){
	}
	void Initialize(){
		arm->SetWristLinked(true);
		arm->SetPivotArmAbs(mSetPoint);
	}
	void Execute(){
		if(false){   //TODO: check if motor is stalled

		}
	}
	bool IsFinished(){
		return arm->IsArmOnTarget();
	}
	void End(){
		arm->SetWristLinked(false);
		arm->StopPivotArm();
	}
	void Interrupted(){
		End();
	}
};

#endif
