#ifndef IntakeTurnOnWithAutoSafety_H
#define IntakeTurnOnWithAutoSafety_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeTurnOnWithAutoSafety: public CommandBase
{
public:
	IntakeTurnOnWithAutoSafety(){
		Requires(intake);
	}
	void Initialize(){
		intake->TurnOn(.75 * INTAKE_FORWARD_SPEED);
		SetTimeout(THREE_TOTE_AUTO_STACK_TIMEOUT);
	}
	void Execute(){
		if (IsTimedOut()){
			CommandGroup* g = GetGroup();

			if (g != NULL){
				g->Cancel();
				driveTrain->Crab(0,0,0);
				stacker->Disable();
				intake->TurnOff();
			}
		}
	}
	bool IsFinished(){
		return intake->IsContained();
	}
	void End(){
		intake->TurnOff();
	}
	void Interrupted(){
		End();
	}
};

#endif
