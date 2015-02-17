#ifndef STACKER_GOTO_BOTTOM_COMMAND_H
#define STACKER_GOTO_BOTTOM_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToBottomCommand: public CommandBase
{
private:
	bool mloaded;
public:
	StackerGoToBottomCommand(bool loaded = false) : CommandBase() {
		Requires(stacker);
		mloaded = loaded;
	}
	void Initialize(){
		if (stacker->GetToteCount() > 5){
			arm->OpenGripper();
		}
		CommandBase::stacker->SetPosition(0.34f, mloaded);
	}
	void Execute() {}
	bool IsFinished(){
		return CommandBase::stacker->GetPosition() < 500;
	}
	void End(){
		CommandBase::stacker->Disable(true, false);
	}
	void Interrupted(){
		End();
	}
};

#endif
