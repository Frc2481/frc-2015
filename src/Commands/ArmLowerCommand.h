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
		SetTimeout(.3);
		arm->SetPivotArmRelative(5.0f);
	}
	void Execute(){}
	bool IsFinished(){
		return arm->IsArmOnTarget() || IsTimedOut();
	}
	void End(){
		arm->StopPivotArm();
	}
	void Interrupted(){
		End();
	}
};

#endif
