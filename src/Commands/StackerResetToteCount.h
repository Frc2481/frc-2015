#ifndef StackerResetToteCount_H
#define StackerResetToteCount_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerResetToteCount: public CommandBase
{
public:
	StackerResetToteCount(){}
	void Initialize(){
		stacker->ResetToteCount();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
