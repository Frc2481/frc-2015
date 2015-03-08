#ifndef ArmShoulderAndWristToTippedOverCanCommand_H
#define ArmShoulderAndWristToTippedOverCanCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmShoulderAndWristToTippedOverCanCommand: public CommandGroup
{
public:
	ArmShoulderAndWristToTippedOverCanCommand() {
		AddSequential(new ArmShoulderToSetPoint(84));
		AddSequential(new ArmWristToSetPointOverride(265));
	}
};

#endif
