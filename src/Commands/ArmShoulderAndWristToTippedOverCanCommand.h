#ifndef ArmShoulderAndWristToTippedOverCanCommand_H
#define ArmShoulderAndWristToTippedOverCanCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmShoulderAndWristToTippedOverCanCommand: public CommandGroup
{
public:
	ArmShoulderAndWristToTippedOverCanCommand(float angle) {
		AddSequential(new ArmWristToTippedOverCan(265));
		AddSequential(new ArmShoulderToFloorTippedOverCan(angle));
	}
};

#endif
