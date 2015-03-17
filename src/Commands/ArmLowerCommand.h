#ifndef ArmLowerCommand_H
#define ArmLowerCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmLowerCommand: public CommandBase
{
public:
	ArmLowerCommand(){
		Requires(arm);
	}
	void Initialize(){
		arm->SetPivotArmRelative(10.0f);
	}
	void Execute(){}
	bool IsFinished(){
		return arm->IsArmOnTarget();
	}
	void End(){
		arm->StopPivotArm();
	}
	void Interrupted(){
		End();
	}
};

#endif
