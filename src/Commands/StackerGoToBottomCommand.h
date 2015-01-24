#ifndef STACKER_GOTO_BOTTOM_COMMAND_H
#define STACKER_GOTO_BOTTOM_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToBottomCommand: public CommandBase
{
public:
	StackerGoToBottomCommand() : CommandBase() {
	}
	void Initialize(){
		CommandBase::stacker->SetPosition(0.0f);
	}
	void Execute() {}
	bool IsFinished(){
		return CommandBase::stacker->OnTarget();
	}
	void End(){
		CommandBase::stacker->Stop();
	}
	void Interrupted(){
		End();
	}
};

#endif
