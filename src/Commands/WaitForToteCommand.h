#ifndef WaitForToteCommand_H
#define WaitForToteCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class WaitForToteCommand: public CommandBase
{
public:
	WaitForToteCommand(){}
	void Initialize(){}
	void Execute(){}
	bool IsFinished(){
		return CommandBase::intake->IsContained();
	}
	void End(){}
	void Interrupted(){}
};

#endif
