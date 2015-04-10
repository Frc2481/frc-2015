#ifndef DriveTrainWaitForHeading_H
#define DriveTrainWaitForHeading_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveTrainWaitForHeading: public CommandBase
{
private:
	double mAngle;
public:
	DriveTrainWaitForHeading(double angle)
		: mAngle(angle) {}
	void Initialize(){}
	void Execute(){}
	bool IsFinished(){
		return fabs(driveTrain->GetHeading() - mAngle) < 2;

	}
	void End(){}
	void Interrupted(){}
};

#endif
