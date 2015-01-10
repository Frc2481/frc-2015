#ifndef StackerResetCommand_H
#define StackerResetCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerResetCommand: public CommandBase
{
public:
	StackerResetCommand() : CommandBase() {
	}

	void Initialize(){
		CommandBase::stacker->Reset();
	}
	void Execute() {}
	bool IsFinished(){
		return !CommandBase::stacker->IsResetting();
	}
	void End(){
		CommandBase::stacker->Stop();
	}
	void Interrupted(){
		End();
	}

};

#endif
