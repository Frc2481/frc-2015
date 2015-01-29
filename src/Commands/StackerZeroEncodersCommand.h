#ifndef StackerZeroEncodersCommand_H
#define StackerZeroEncodersCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerZeroEncodersCommand: public CommandBase
{
public:
	StackerZeroEncodersCommand(){}
	void Initialize(){
		CommandBase::stacker->Reset();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
