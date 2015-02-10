#ifndef PickUpToteToScoringPlatform_H
#define PickUpToteToScoringPlatform_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "StackerGoToBottomCommand.h"
#include "StackerGoToScoringPlatformCommand.h"

class PickUpToteToScoringPlatformCommand: public CommandGroup
{
public:
	PickUpToteToScoringPlatformCommand(){
		AddSequential(new StackerGoToBottomCommand());
		//AddSequential(new WaitCommand(.2));
		AddSequential(new StackerGoToScoringPlatformCommand());
	}
};

#endif
