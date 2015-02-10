#ifndef ArmLowerCommand_H
#define ArmLowerCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmLowerCommand: public CommandBase
{
public:
	ArmLowerCommand(){}
	void Initialize(){
		arm->SetPivotArmRelative(-5.0f);
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
