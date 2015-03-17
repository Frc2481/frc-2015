#ifndef IntakeTurnOn_H
#define IntakeTurnOn_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeTurnOn: public CommandBase
{
public:
	IntakeTurnOn(){
		Requires(intake);
	}
	void Initialize(){
		intake->TurnOn();
	}
	void Execute(){
		intake->IntakeManual(oi->GetAuxRightStick()->GetRawAxis(0));
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
