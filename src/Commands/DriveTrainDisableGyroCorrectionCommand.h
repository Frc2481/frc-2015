#ifndef DriveTrainDisableGyroCorrectionCommand_H
#define DriveTrainDisableGyroCorrectionCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveTrainDisableGyroCorrectionCommand: public CommandBase
{
public:
	DriveTrainDisableGyroCorrectionCommand() {}
	void Initialize() {
		driveTrain->SetGyroCorrection(false);
	}
	void Execute() {}
	bool IsFinished() { return true; }
	void End() {}
	void Interrupted() {}
};

#endif
