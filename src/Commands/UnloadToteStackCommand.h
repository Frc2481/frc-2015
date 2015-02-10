#ifndef UnloadToteStackCommand_H
#define UnloadToteStackCommand_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class UnloadToteStackCommand: public CommandGroup
{
public:
	UnloadToteStackCommand(){
		AddSequential(new StackerGoToBottomCommand(true));
		AddParallel(new IntakeTurnOnReverse());
		AddSequential(new AutoDriveCommand(0,-1,0,1));
		AddSequential(new IntakeTurnOff());
		AddSequential(new AutoDriveCommand(0,0,0,0));
	}
};

#endif
