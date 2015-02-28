#ifndef DriveTrainEnableGyroCorrectionCommand_H
#define DriveTrainEnableGyroCorrectionCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveTrainEnableGyroCorrectionCommand: public CommandBase
{
public:
	DriveTrainEnableGyroCorrectionCommand() {}
	void Initialize() {
		driveTrain->SetGyroCorrection(true);
	}
	void Execute() {}
	bool IsFinished() { return true; }
	void End() {}
	void Interrupted() {}
};

#endif
