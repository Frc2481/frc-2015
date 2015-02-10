#ifndef ArmGripperCloseCommand_H
#define ArmGripperCloseCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmGripperCloseCommand: public CommandBase
{
public:
	ArmGripperCloseCommand(){}
	void Initialize(){
		arm->CloseGripper();
	}
	void Execute(){}
	bool IsFinished(){
		return !arm->IsGripper();
	}
	void End(){}
	void Interrupted(){}
};

#endif
