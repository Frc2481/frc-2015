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
		if (fabs(arm->GetShoulderAngle() - ARM_STEP_HEIGHT) < 2) {
			arm->SetPivotArmAbs(ARM_STEP_HEIGHT_EXTENDED);
		}
	}
	void Execute(){}
	bool IsFinished(){
		return arm->IsExtended() && arm->IsArmOnTarget();
	}
	void End(){}
	void Interrupted(){}
};

#endif
