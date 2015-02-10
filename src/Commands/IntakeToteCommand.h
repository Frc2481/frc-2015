#ifndef IntakeToteCommand_H
#define IntakeToteCommand_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class IntakeToteCommand: public CommandGroup
{
public:
	IntakeToteCommand(){
		AddSequential(new StackerGoToTopCommand());
		AddSequential(new IntakeTurnOn());

	}
};

#endif
