#ifndef StackerDisableBrakeCommand_H
#define StackerDisableBrakeCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerDisableBrakeCommand: public CommandBase
{
public:
	StackerDisableBrakeCommand(){}
	void Initialize(){
		CommandBase::stacker->Enable(false);
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		CommandBase::stacker->Disable();
	}
	void Interrupted(){
		End();
	}
};

#endif
