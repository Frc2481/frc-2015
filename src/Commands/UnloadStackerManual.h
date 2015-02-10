#ifndef UnloadStackerManual_H
#define UnloadStackerManual_H

#include "../CommandBase.h"
#include "WPILib.h"

class UnloadStackerManual: public CommandBase
{
public:
	UnloadStackerManual(){
		Requires(driveTrain);
		Requires(intake);
	}
	void Initialize(){
		driveTrain->SetFieldCentric(false);
	}
	void Execute(){
		intake->TurnOnReverse();

		driveTrain->Crab(0,.3,0);   //!!this relies on boost being false
	}
	bool IsFinished(){
		return false;
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
