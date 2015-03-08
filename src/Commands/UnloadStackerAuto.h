#ifndef UnloadStackerAuto_H
#define UnloadStackerAuto_H

#include "../CommandBase.h"
#include "WPILib.h"

class UnloadStackerAuto: public CommandBase
{
public:
	UnloadStackerAuto() {
		Requires(driveTrain);
		Requires(intake);
	}
	void Initialize(){
		driveTrain->SetFieldCentric(false);
		stacker->ResetToteCount();
		SetTimeout(1.5);
	}
	void Execute(){
		intake->TurnOnReverse();

		driveTrain->Crab(0,.5,0);   //!!this relies on boost being false
	}
	bool IsFinished(){
		return IsTimedOut();
	}
	void End(){
		intake->TurnOff();
		driveTrain->Crab(0,0,0);
	}
	void Interrupted(){
		End();
	}
};

#endif
