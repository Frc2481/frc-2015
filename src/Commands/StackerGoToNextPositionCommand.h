#ifndef STACKER_GOTO_NEXT_POSITION_COMMAND_H
#define STACKER_GOTO_NEXT_POSITION_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToNextPositionCommand: public CommandBase
{
private:
	int mPos;
	bool mSkipOnTarget;
public:
	StackerGoToNextPositionCommand() : CommandBase() {
		Requires(stacker);
		mSkipOnTarget = false;
	}
	void Initialize(){
		if(stacker->GetToteCount() < 5){
			mPos = 15.25f;
		}
		else {
			mPos = 3.0f;
		}

		if (stacker->GetToteCount() >= 4){
			arm->OpenGripper();
		}

		if (CommandBase::stacker->GetPosition() < ((mPos - 1) * 578)){
			CommandBase::stacker->SetPosition(mPos);
			mSkipOnTarget = false;
		} else {
			mSkipOnTarget = true;
		}
	}
	void Execute() {}
	bool IsFinished(){
		return (CommandBase::stacker->GetPosition() > (mPos * 578)) || mSkipOnTarget;
	}
	void End(){
		CommandBase::stacker->Disable();
		arm->CloseGripper();
//		CommandBase::stacker->UpdateToteCount();
	}
	void Interrupted(){
		End();
	}
};

#endif
