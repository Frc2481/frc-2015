#ifndef StackerTurnOff_H
#define StackerTurnOff_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerTurnOff: public CommandBase
{
public:
	StackerTurnOff(){}
	void Initialize(){
		CommandBase::stacker->Disable();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
