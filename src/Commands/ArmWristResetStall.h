#ifndef ArmWristResetStall_H
#define ArmWristResetStall_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmWristResetStall: public CommandBase
{
public:
	ArmWristResetStall(){}
	void Initialize(){
		arm->SetStalled(false);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
