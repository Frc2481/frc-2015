#ifndef ArmGoToTopCommand_H
#define ArmGoToTopCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmGoToPositionCommand: public CommandBase
{

private:
	float mPosition;

public:
	ArmGoToPositionCommand(float position){
		Requires(arm);
		mPosition = position;
	}
	void Initialize(){
		arm->SetPivotArmAbs(mPosition);
	}
	void Execute(){
		if(arm->IsLocked()) {
			arm->SetWristAbs(5- arm->GetPivotPos());
		}
	}
	bool IsFinished(){
		return arm->IsLiftOnTarget();
	}
	void End(){
		arm->StopPivotArm();
	}
	void Interrupted(){
		End();
	}
};

#endif
