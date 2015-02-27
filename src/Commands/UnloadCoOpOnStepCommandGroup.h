#ifndef UnloadCoOpOnStepCommandGroup_H
#define UnloadCoOpOnStepCommandGroup_H

#include "Commands/CommandGroup.h"
#include "Commands/StackerGoToPositionCommand.h"
#include "Commands/ExtendSlideCommand.h"
#include "Commands/RetractSlideCommand.h"
#include "Commands/StackerGoToTopCommand.h"
#include "Commands/StackerResetToteCount.h"
#include "WPILib.h"

class UnloadCoOpOnStepCommandGroup: public CommandGroup
{
public:
	UnloadCoOpOnStepCommandGroup(){
		//AddSequential(new StackerGoToPositionCommand(10));
		AddSequential(new ExtendSlideCommand());
		AddSequential(new WaitCommand(1.2));
		AddSequential(new StackerGoToPositionCommand(STEP_HEIGHT));
		AddSequential(new RetractSlideCommand());
		AddSequential(new WaitCommand(1.5));
		AddSequential(new StackerResetToteCount());
	}
};

#endif
