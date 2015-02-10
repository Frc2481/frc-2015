#ifndef StackerBrakeCommand_H
#define StackerBrakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerBrakeCommand: public CommandBase
{
public:
	StackerBrakeCommand(){}
	void Initialize(){
		CommandBase::stacker->Disable();
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		CommandBase::stacker->Enable();
	}
	void Interrupted(){}
};

#endif
