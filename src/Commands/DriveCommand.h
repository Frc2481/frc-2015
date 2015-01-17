#ifndef DriveCommand_H
#define DriveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveCommand: public CommandBase
{
public:
	DriveCommand();
	void Initialize();
	void Execute() {
		driveTrain->Crab(oi->GetDriverStick()->GetRawAxis(XboxController::xbLeftXAxis),
				         oi->GetDriverStick()->GetRawAxis(XboxController::xbLeftYAxis),
						 oi->GetDriverStick()->GetRawAxis(XboxController::xbRightXAxis));
	}
	bool IsFinished(){
		return false;
	}
	void End();
	void Interrupted();
};

#endif
