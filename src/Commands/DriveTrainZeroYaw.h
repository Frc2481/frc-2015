#ifndef DriveTrainZeroYaw_H
#define DriveTrainZeroYaw_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveTrainZeroYaw: public CommandBase
{
public:
	DriveTrainZeroYaw(){}
	void Initialize(){
		driveTrain->ZeroYaw();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
