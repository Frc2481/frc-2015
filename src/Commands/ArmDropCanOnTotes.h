#ifndef ArmDropCanOnTotes_H
#define ArmDropCanOnTotes_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class ArmDropCanOnTotes: public CommandGroup
{
public:
	ArmDropCanOnTotes(){
		AddSequential(new ArmGripperOpenCommand());
		AddSequential(new WaitCommand(.25));
		AddParallel(new AutoDriveCommand(0,.3,0,.3));
		AddSequential(new ArmLowerCommand());
	}
};

#endif
