#ifndef AquireToteCommand_H
#define AquireToteCommand_H

#include <Commands/PickUpToteCommand.h>
#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "IntakeToteCommand.h"

class AcquireToteCommand: public CommandGroup
{
public:
	AcquireToteCommand(){
		AddSequential(new IntakeToteCommand());
		AddSequential(new PickUpToteCommand());
	}
};

#endif
