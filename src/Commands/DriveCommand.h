#ifndef DriveCommand_H
#define DriveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class DriveCommand: public CommandBase
{
public:
	DriveCommand(){
		Requires(driveTrain);
	}
	void Initialize(){}
	void Execute() {
		double x = oi->GetDriverStick()->GetRawAxis(XboxController::xbLeftXAxis, oi->GetBoosting());
		double y = oi->GetDriverStick()->GetRawAxis(XboxController::xbLeftYAxis, oi->GetBoosting());
		double z = oi->GetDriverStick()->GetRawAxis(XboxController::xbRightXAxis, oi->GetBoosting());

//		if (fabs(x) < .2) x = 0;
//		if (fabs(y) < .2) y = 0;
//		if (fabs(z) < .2) z = 0;

//		double wrist = oi->GetAuxStick()->GetRawAxis(XboxController::xbLeftYAxis);
//		if (fabs(wrist) > .2) {
//			arm->SetWristManual(wrist);
//		}

		if (stacker->IsEnabled() && !stacker->OnTarget() && stacker->GetToteCount() > 0) {
			x /= 2;
			y /= 2;
			z /= 2;
		}

		if (!DriverStation::GetInstance()->IsAutonomous()) {
			driveTrain->Crab(x,y,z);
		}
	}
	bool IsFinished(){
		return false;
	}
	void End(){}
	void Interrupted(){}
};

#endif
