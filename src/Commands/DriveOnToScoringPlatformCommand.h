#ifndef DriveOnToScoringPlatformCommand_H
#define DriveOnToScoringPlatformCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveOnToScoringPlatformCommand: public CommandBase
{
private:
	bool _done;
public:
	DriveOnToScoringPlatformCommand() {
		Requires(driveTrain);
	}
	void Initialize() {
		_done = false;
		driveTrain->SetBrake(true);
		driveTrain->Crab(0, .4, 0);
	}
	void Execute() {
		if (driveTrain->GetIMU()->GetRoll() < -1.5 && !_done) {
			driveTrain->Crab(0,0,0);
			SetTimeout(TimeSinceInitialized() + .5);
			_done = true;
		}
	}
	bool IsFinished() {
		return IsTimedOut();
	}
	void End() {
		driveTrain->Crab(0,0,0);
		driveTrain->SetBrake(false);
	}
	void Interrupted() {
		End();
	}
};

#endif
