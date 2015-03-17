#ifndef ArmGripperOpenMomentaryCommand_H
#define ArmGripperOpenMomentaryCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmGripperOpenMomentaryCommand: public CommandBase
{
public:
	ArmGripperOpenMomentaryCommand(){}
	void Initialize(){
		arm->OpenGripper();
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		arm->CloseGripper();
	}
	void Interrupted(){
		End();
	}
};

#endif
