#ifndef IntakeTurnOn_H
#define IntakeTurnOn_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeTurnOn: public CommandBase
{
public:
	IntakeTurnOn(){}
	void Initialize(){
		CommandBase::intake->TurnOn();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
