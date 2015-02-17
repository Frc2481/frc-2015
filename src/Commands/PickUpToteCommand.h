#ifndef PickUpTote_H
#define PickUpTote_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "StackerGoToBottomCommand.h"
#include "StackerGoToNextPositionCommand.h"
#include "IncrementToteCountCommand.h"

class PickUpToteCommand: public CommandGroup
{
public:
	PickUpToteCommand(){
		AddSequential(new IncrementToteCountCommand());
		AddSequential(new StackerGoToBottomCommand());
		//AddSequential(new WaitCommand(.2));
		AddSequential(new StackerGoToNextPositionCommand());
	}
};

#endif
