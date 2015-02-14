#ifndef ExtendSlideCommand_H
#define ExtendSlideCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ExtendSlideCommand: public CommandBase
{
public:
	ExtendSlideCommand(){}
	void Initialize(){
		slide->Extend();
	}
	void Execute(){}
	bool IsFinished(){
		return slide->Get();
	}
	void End(){}
	void Interrupted(){}
};

#endif
