#ifndef AcquireToteAutoCommandGroup_H
#define AcquireToteAutoCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "StackerGoToNextPositionCommand.h"
#include "StackerGoToBottomCommand.h"
#include "IncrementToteCountCommand.h"
#include "StackerGoToTopCommand.h"
#include "IntakeTurnOnWithAutoSafety.h"

class AcquireToteAutoCommandGroup: public CommandGroup
{
public:
	AcquireToteAutoCommandGroup(){
		AddSequential(new StackerGoToTopCommand());
		AddSequential(new IntakeTurnOnWithAutoSafety());
		AddSequential(new IncrementToteCountCommand());
		AddSequential(new StackerGoToBottomCommand());
		AddSequential(new StackerGoToNextPositionCommand());
	}
};

#endif
