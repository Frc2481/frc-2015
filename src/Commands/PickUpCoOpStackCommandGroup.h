#ifndef PickUpCoOpStackCommandGroup_H
#define PickUpCoOpStackCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "RobotParameters.h"
#include "AutoDriveCommand.h"
#include "IntakeTurnOn.h"
#include "StackerGoToBottomCommand.h"
#include "StackerGoToPositionCommand.h"

class PickUpCoOpStackCommandGroup: public CommandGroup
{
public:
	PickUpCoOpStackCommandGroup(){
		AddSequential(new StackerGoToPositionCommand(STEP_HEIGHT));
		//AddParallel(new AutoDriveCommand(0,-.2,0,1));
		AddSequential(new IntakeTurnOn());
		//AddSequential(new AutoDriveCommand(0,0,0));
		AddSequential(new StackerGoToBottomCommand());
		AddSequential(new StackerGoToPositionCommand(ABOVE_STEP_HEIGHT));

	}
};

#endif
