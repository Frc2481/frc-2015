#ifndef AcquireRCFromStepCommandGroup_H
#define AcquireRCFromStepCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class AcquireRCFromStepCommandGroup: public CommandGroup
{
public:
	AcquireRCFromStepCommandGroup(){
		AddSequential(new ArmGripperOpenCommand());
		AddSequential(new ArmExtendCommand());
		AddSequential(new WaitCommand(1));
		AddSequential(new ArmGripperCloseCommand());
		AddSequential(new WaitCommand(.25));
		AddSequential(new ArmGoToPositionCommand(75));
		AddSequential(new ArmRetractCommand());
		AddSequential(new WaitCommand(.7));
		AddSequential(new ArmGoToPositionCommand(5));
		AddSequential(new AutoDriveCommand(0,-1,1,.5));
	}
};

#endif
