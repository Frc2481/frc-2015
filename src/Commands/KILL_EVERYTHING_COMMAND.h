#ifndef KILL_EVERYTHING_COMMAND_H
#define KILL_EVERYTHING_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"

class KILL_EVERYTHING_COMMAND: public CommandBase
{
public:
	KILL_EVERYTHING_COMMAND(){}
	void Initialize(){
		Scheduler::GetInstance()->RemoveAll();
		arm->StopPivotArm();
		arm->StopPivotWrist();
		stacker->Disable();

	}
	void Execute(){}
	bool IsFinished(){ return true; }
	void End(){}
	void Interrupted(){}
};

#endif
