#ifndef ArmGripperOpenCommand_H
#define ArmGripperOpenCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmGripperOpenCommand: public CommandBase
{
public:
	ArmGripperOpenCommand(){}
	void Initialize(){
		arm->OpenGripper();
	}
	void Execute(){}
	bool IsFinished(){
		return arm->IsGripper();
	}
	void End(){}
	void Interrupted(){}
};

#endif
