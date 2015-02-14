#ifndef STACKER_GO_TO_STEP_COMMAND_H
#define STACKER_GO_TO_STEP_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToStepCommand: public CommandBase
{
public:
	StackerGoToStepCommand() : CommandBase() {
		Requires(stacker);
	}
	void Initialize(){
		CommandBase::stacker->SetPosition(6.7f);
	}
	void Execute() {}
	bool IsFinished(){
		return CommandBase::stacker->OnTarget();
	}
	void End(){
		CommandBase::stacker->Disable();
//		CommandBase::stacker->UpdateToteCount();
	}
	void Interrupted(){
		End();
	}
};

#endif
