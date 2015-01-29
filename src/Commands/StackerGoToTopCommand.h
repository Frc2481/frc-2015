#ifndef STACKER_GOTO_TOP_COMMAND_H
#define STACKER_GOTO_TOP_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToTopCommand: public CommandBase
{
public:
	StackerGoToTopCommand() : CommandBase() {
	}
	void Initialize(){
		CommandBase::stacker->SetPosition(13.0f);
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
