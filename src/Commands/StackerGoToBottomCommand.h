#ifndef STACKER_GOTO_BOTTOM_COMMAND_H
#define STACKER_GOTO_BOTTOM_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToBottomCommand: public CommandBase
{
protected:
	bool mloaded;
public:
	StackerGoToBottomCommand(bool loaded = false) : CommandBase() {
		Requires(stacker);
		mloaded = loaded;
	}
	virtual void Initialize(){
		if (stacker->GetToteCount() >= 5){
			arm->OpenGripper();
		}
		CommandBase::stacker->SetPosition(0.34f, mloaded);
	}
	void Execute() {}
	virtual bool IsFinished(){
		return CommandBase::stacker->GetPosition() < 500;
	}
	void End(){
		stacker->Disable(true, false);
	}
	void Interrupted(){
		stacker->Disable();
	}
};

class StackerGoToBottomUnloadCommand : public StackerGoToBottomCommand {
public:
	StackerGoToBottomUnloadCommand(bool loaded = false) : StackerGoToBottomCommand(loaded) {
	}

	void Initialize(){
			if (stacker->GetToteCount() >= 5){
				arm->OpenGripper();
				SetTimeout(.1);
			}
			else {
				SetTimeout(0);
			}
			CommandBase::stacker->SetPosition(0.34f, mloaded);
	}

	bool IsFinished() {
		return StackerGoToBottomCommand::IsFinished() && IsTimedOut();
	}
};

#endif
