#ifndef ArmShoulderAndWristToStepCommand_H
#define ArmShoulderAndWristToStepCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmShoulderAndWristToStepCommand: public CommandGroup
{
public:
	ArmShoulderAndWristToStepCommand() {
		AddSequential(new ArmShoulderToSetPoint(76));
		AddSequential(new ArmWristToSetPoint(190));
	}
};

#endif
