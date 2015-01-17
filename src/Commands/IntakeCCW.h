#ifndef IntakeCCW_H
#define IntakeCCW_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeCCW: public CommandBase
{
public:
	IntakeCCW(){}
	void Initialize(){
		CommandBase::intake->RotateCCW();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
