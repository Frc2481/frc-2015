#ifndef IncrementToteCountCommand_H
#define IncrementToteCountCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class IncrementToteCountCommand: public CommandBase
{
public:
	IncrementToteCountCommand(){}
	void Initialize(){
		stacker->IncrementToteCount();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
