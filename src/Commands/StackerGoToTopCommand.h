#ifndef STACKER_GOTO_TOP_COMMAND_H
#define STACKER_GOTO_TOP_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToTopCommand: public CommandBase
{
private:
	bool mSkipOnTarget;
public:
	StackerGoToTopCommand() : CommandBase() {
		Requires(stacker);
		mSkipOnTarget = false;
	}
	void Initialize(){
		if (CommandBase::stacker->GetPosition() < (10.25 * 578)){
			CommandBase::stacker->SetPosition(15.25f);
			mSkipOnTarget = false;
		} else {
			mSkipOnTarget = true;
		}
	}
	void Execute() {}
	bool IsFinished(){
		return (CommandBase::stacker->GetPosition() > (15.57 * 578)) || mSkipOnTarget;
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
