#ifndef MOVE_FORWARD_COMMAND_H
#define MOVE_FORWARD_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"

class MoveForwardCommand: public CommandBase
{
public:
	MoveForwardCommand();
	void Initialize(){
		driveTrain->Crab(0,1,0);

		WaitCommand(.1);
	}
	void Execute();
	bool IsFinished(){
		return true;
	}
	void End(){
		driveTrain->Stop();
	}
	void Interrupted();
};

#endif
