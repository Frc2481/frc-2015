#ifndef ArmShoulderAndWristToStepCommand_H
#define ArmShoulderAndWristToStepCommand_H

#include "../CommandBase.h"
#include "RobotParameters.h"
#include "WPILib.h"

class ArmShoulderAndWristToStepCommand: public CommandGroup
{
public:
	ArmShoulderAndWristToStepCommand() {
		AddSequential(new ArmShoulderToSetPoint(ARM_STEP_HEIGHT));
		AddSequential(new ArmWristToSetPoint(190));
	}
};

#endif
