#ifndef IntakeTurnOnReverse_H
#define IntakeTurnOnReverse_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeTurnOnReverse: public CommandBase
{
public:
	IntakeTurnOnReverse(){}
	void Initialize(){
		CommandBase::intake->TurnOnReverse();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
