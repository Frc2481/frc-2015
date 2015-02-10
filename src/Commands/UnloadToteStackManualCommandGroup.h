#ifndef UnloadToteStackCommandGroup_H
#define UnloadToteStackCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "StackerResetToteCount.h"

class UnloadToteStackCommandGroup: public CommandGroup
{
public:
	UnloadToteStackCommandGroup(){
		AddSequential(new StackerGoToBottomCommand(true));
		AddSequential(new UnloadStackerManual());
		AddSequential(new StackerResetToteCount());
	}
};

#endif
