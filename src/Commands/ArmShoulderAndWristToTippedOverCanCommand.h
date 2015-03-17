#ifndef ArmShoulderAndWristToTippedOverCanCommand_H
#define ArmShoulderAndWristToTippedOverCanCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmShoulderAndWristToTippedOverCanCommand: public CommandGroup
{
public:
	ArmShoulderAndWristToTippedOverCanCommand() {
		AddSequential(new ArmWristToTippedOverCan(265));
		AddSequential(new ArmShoulderToFloorTippedOverCan(SHOULDER_TIPPED_OVER_CAN));
	}
};

#endif
