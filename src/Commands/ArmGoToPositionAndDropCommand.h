#ifndef ArmGoToPositionAndDropCommand_H
#define ArmGoToPositionAndDropCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmGoToPositionAndDropCommand: public CommandBase
{

private:
	float mPosition;
	int tc;
public:
	ArmGoToPositionAndDropCommand(float position){
		Requires(arm);
		mPosition = position;
		tc = stacker->GetToteCount();
	}
	void Initialize(){
		if(tc < 5)
			arm->SetPivotArmAbs(mPosition);
	}
	void Execute(){}
	bool IsFinished(){
		return arm->IsArmOnTarget();
	}
	void End(){
		arm->StopPivotArm();
		if(tc < 5)
			arm->OpenGripper();
	}
	void Interrupted(){
		End();
	}
};

#endif
