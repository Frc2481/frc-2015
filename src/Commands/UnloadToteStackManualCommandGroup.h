#ifndef UnloadToteStackCommandGroup_H
#define UnloadToteStackCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "StackerResetToteCount.h"
#include "ArmGripperOpenCommand.h"
#include "ArmGoToPositionAndDropCommand.h"

class UnloadToteStackCommandGroup: public CommandGroup
{
public:
	UnloadToteStackCommandGroup(){
		//AddSequential(new ArmGripperOpenCommand());
		AddSequential(new StackerGoToBottomCommand(true));
		//AddParallel(new ArmGoToPositionAndDropCommand(40));
		AddSequential(new StackerResetToteCount());
		AddSequential(new UnloadStackerManual());
	}
};

#endif
