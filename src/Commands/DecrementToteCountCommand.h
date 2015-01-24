#ifndef DecrementToteCountCommand_H
#define DecrementToteCountCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DecrementToteCountCommand: public CommandBase
{
public:
	DecrementToteCountCommand(){}
	void Initialize(){
		stacker->DecrementToteCount();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
