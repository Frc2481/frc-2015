#ifndef IntakeTurnOnReverse_H
#define IntakeTurnOnReverse_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeTurnOnReverse: public CommandBase
{
public:
	IntakeTurnOnReverse(){
		Requires(intake);
	}
	void Initialize(){
		CommandBase::intake->TurnOnReverse();
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		CommandBase::intake->TurnOff();
	}
	void Interrupted(){
		End();
	}
};

#endif
