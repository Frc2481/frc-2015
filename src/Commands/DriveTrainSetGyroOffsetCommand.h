#ifndef DriveTrainSetGyroOffsetCommand_H
#define DriveTrainSetGyroOffsetCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveTrainSetGyroOffsetCommand: public CommandBase
{
private:
	double mOffset;
public:
	DriveTrainSetGyroOffsetCommand(double offset)
		: mOffset(offset){
	}
	void Initialize(){
		driveTrain->SetGyroCorrectionOffset(mOffset);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
