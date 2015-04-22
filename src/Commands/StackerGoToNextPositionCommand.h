#ifndef STACKER_GOTO_NEXT_POSITION_COMMAND_H
#define STACKER_GOTO_NEXT_POSITION_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToNextPositionCommand: public CommandBase
{
private:
	float mPos;
	bool mSkipOnTarget;
public:
	StackerGoToNextPositionCommand() : CommandBase() {
		Requires(stacker);
		mSkipOnTarget = false;
	}
	void Initialize(){
		if(stacker->GetToteCount() < stacker->getDesiredToteCount()){
			mPos = 15.0f;   //changed from 15.25
		}
		else {
			mPos = 3.0f;
		}

		if (stacker->GetToteCount() >= 4){
			arm->SetGripperShudder(true);
			SetTimeout(2);
		}

		if (CommandBase::stacker->GetPosition() < ((mPos - 2) * 578)){
			CommandBase::stacker->SetPosition(mPos);
			mSkipOnTarget = false;
		} else {
			mSkipOnTarget = true;
		}
	}
	void Execute() {
		if (IsTimedOut() &&
			stacker->GetToteCount() >= 4) {
			arm->SetGripperShudder(false);
			arm->OpenGripper();
		}
	}
	bool IsFinished(){
		return (CommandBase::stacker->GetPosition() > (mPos * 578)) || mSkipOnTarget;
	}
	void End(){
		CommandBase::stacker->Disable();
		if (stacker->GetToteCount() >= 4){
			arm->SetGripperShudder(false);
			arm->CloseGripper();
		}
	}
	void Interrupted(){
		End();
	}
};

#endif
