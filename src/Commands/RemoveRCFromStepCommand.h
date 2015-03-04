#ifndef RemoveRCFromStepCommand_H
#define RemoveRCFromStepCommand_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

#include "ArmShoulderToSetPoint.h"
#include "ArmGripperCloseCommand.h"
#include "ArmGripperOpenCommand.h"
#include "ArmExtendCommand.h"
#include "ArmRetractCommand.h"
#include "AutoDriveCommand.h"

class RemoveRCFromStepCommand: public CommandGroup
{
public:
	RemoveRCFromStepCommand() {
		AddParallel(new AutoDriveCommand(0,-.2, 0,1.2));
		AddSequential(new ArmShoulderToSetPoint(82));
		AddSequential(new ArmGripperOpenCommand());
		AddSequential(new ArmExtendCommand());
		AddSequential(new WaitCommand(1));
		AddSequential(new ArmGripperCloseCommand());
		AddSequential(new WaitCommand(.25));
		AddSequential(new ArmShoulderToSetPoint(65));
		AddSequential(new ArmRetractCommand());
		AddParallel(new AutoDriveCommand(0,.3, 0,4.5));
		AddSequential(new ArmShoulderToSetPoint(5));
		//AddSequential(new WaitCommand(.7));
		//AddSequential(new ArmGripperOpenCommand());


	}
};

#endif
