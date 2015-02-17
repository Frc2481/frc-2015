#ifndef StackerGoToPositionCommand_H
#define StackerGoToPositionCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToPositionCommand: public CommandBase
{
private:
	float mPosition;
public:
	StackerGoToPositionCommand(float pos)
	:mPosition(pos){
	}
	void Initialize(){
		stacker->SetPosition(mPosition);
	}
	void Execute(){}
	bool IsFinished(){
		return stacker->OnTarget();
	}
	void End(){
		stacker->Disable();
	}
	void Interrupted(){
		End();
	}
};

#endif
