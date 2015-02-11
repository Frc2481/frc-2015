#ifndef ArmExtendCommand_H
#define ArmExtendCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmExtendCommand: public CommandBase
{
public:
	ArmExtendCommand(){
		Requires(arm);
	}
	void Initialize(){
		arm->ExtendArm();
	}
	void Execute(){}
	bool IsFinished(){
		return arm->IsExtended();
	}
	void End(){}
	void Interrupted(){}
};

#endif
