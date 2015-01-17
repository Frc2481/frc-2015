#ifndef ArmToggleLock_H
#define ArmToggleLock_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmToggleLockCommand: public CommandBase
{
public:
	ArmToggleLockCommand(){
		Requires(arm);
	}
	void Initialize(){
		CommandBase::arm->ToggleLock();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
