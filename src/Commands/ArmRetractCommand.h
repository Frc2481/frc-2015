#ifndef ArmRetractCommand_H
#define ArmRetractCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmRetractCommand: public CommandBase
{
public:
	ArmRetractCommand(){
		Requires(arm);
	}
	void Initialize(){
		arm->RetractArm();
	}
	void Execute(){}
	bool IsFinished(){
		return !arm->IsExtended();
	}
	void End(){}
	void Interrupted(){}
};

#endif
