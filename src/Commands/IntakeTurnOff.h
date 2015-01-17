#ifndef IntakeTurnOff_H
#define IntakeTurnOff_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeTurnOff: public CommandBase
{
public:
	IntakeTurnOff(){}
	void Initialize(){
		CommandBase::intake->TurnOff();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
