#ifndef UnloadToteStackCommandGroup_H
#define UnloadToteStackCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "StackerResetToteCount.h"
#include "ArmGripperOpenCommand.h"
#include "ArmGoToPositionAndDropCommand.h"
#include "UnloadStackerAuto.h"
#include "UnloadStackerManual.h"

class UnloadToteStackCommandGroup: public CommandGroup
{
public:
	UnloadToteStackCommandGroup(bool autoMode = false){
		//AddSequential(new ArmGripperOpenCommand());
		//AddParallel(new ArmGoToPositionAndDropCommand(40));
		//AddSequential(new StackerResetToteCount());

		if (autoMode) {
			AddSequential(new UnloadStackerAuto());
		}
		else {
			AddSequential(new StackerGoToBottomUnloadCommand(true));
			AddSequential(new UnloadStackerManual());
		}
	}
};

#endif
