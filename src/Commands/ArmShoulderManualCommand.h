#ifndef ArmShoulderManualCommand_H
#define ArmShoulderManualCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmShoulderManualCommand: public CommandBase
{
private:
	double mSpeed;
public:
	ArmShoulderManualCommand(double speed)
		:mSpeed(speed){
		Requires(arm);
	}
	void Initialize(){
		arm->SetShoulderManual(mSpeed);
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		arm->SetShoulderManual(0);
	}
	void Interrupted(){
		End();
	}
};

#endif
