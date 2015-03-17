#ifndef ArmUnloadCanFour_H
#define ArmUnloadCanFour_H

#include "Commands/CommandGroup.h"
#include "RobotParameters.h"
#include "WPILib.h"

class ArmUnloadCanFour: public CommandGroup
{
public:
	ArmUnloadCanFour(){
		AddSequential(new ArmShoulderToSetPoint(FOUR_TOTE_HEIGHT));
		AddSequential(new ArmWristToSetPoint(235));
	}
};

#endif
