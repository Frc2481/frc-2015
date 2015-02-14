#ifndef RetractSlideCommand_H
#define RetractSlideCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class RetractSlideCommand: public CommandBase
{
public:
	RetractSlideCommand(){}
	void Initialize(){
		slide->Retract();
	}
	void Execute(){}
	bool IsFinished(){
		return slide->Get();
	}
	void End(){}
	void Interrupted(){}
};

#endif
