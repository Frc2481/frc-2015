#ifndef MoveAroundRCCommand_H
#define MoveAroundRCCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class MoveAroundRCCommand: public CommandBase
{
public:
	MoveAroundRCCommand(bool isRight);
	void Initialize(){
		SetTimeout(1);
		if (isRight == true){
						driveTrain->Crab(-1,1,0);
				}
				else if (isRight == false){
						driveTrain->Crab(1,1,0);
				}


	}
	void Execute();
	bool IsFinished(){
		return IsTimedOut();
	}
	void End(){
		driveTrain->Stop();
	}
	void Interrupted();

};

#endif
