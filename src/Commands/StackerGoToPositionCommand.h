#ifndef StackerGoToPositionCommand_H
#define StackerGoToPositionCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToPositionCommand: public CommandBase
{
private:
	float mPosition;
	bool mDown;
public:
	StackerGoToPositionCommand(float pos)
	:mPosition(pos){
	}
	void Initialize(){
		stacker->SetPosition(mPosition);
		if (stacker->GetPosition() > mPosition * 578) {
			mDown = true;
		} else {
			mDown = false;
		}
		stacker->Enable();
	}
	void Execute(){}
	bool IsFinished(){
		if (mDown && stacker->GetPosition() < (mPosition * 578))
			return true;
		if (!mDown && stacker->GetPosition() > (mPosition * 578))
			return true;
		return false;
	}
	void End(){
		stacker->Disable();
	}
	void Interrupted(){
		End();
	}
};

#endif
