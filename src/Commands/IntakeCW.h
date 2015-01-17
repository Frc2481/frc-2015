#ifndef IntakeCW_H
#define IntakeCW_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeCW: public CommandBase
{
public:
	IntakeCW(){}
	void Initialize(){
		CommandBase::intake->RotateCW();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
