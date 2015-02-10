#ifndef StackerManualCommand_H
#define StackerManualCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerManualCommand: public CommandBase
{
public:
	StackerManualCommand(){
		Requires(stacker);
	}
	void Initialize(){
		CommandBase::stacker->Enable(false);
	}
	void Execute(){
		float yValue = CommandBase::oi->GetAuxStick()->GetY();
		CommandBase::stacker->Set(yValue);
	}
	bool IsFinished(){
		return false;
	}
	void End(){
		CommandBase::stacker->Disable();
	}
	void Interrupted(){
		End();
	}
};

#endif
