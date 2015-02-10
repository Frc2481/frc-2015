#ifndef ArmRaiseCommand_H
#define ArmRaiseCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmRaiseCommand: public CommandBase
{
public:
	ArmRaiseCommand(){}
	void Initialize(){
		arm->SetPivotArmRelative(5.0f);
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
