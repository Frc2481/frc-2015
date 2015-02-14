#ifndef AutoContainersFromStepCommandGroup_H
#define AutoContainersFromStepCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "ArmGoToPositionCommand.h"
#include "ArmGripperCloseCommand.h"
#include "ArmGripperOpenCommand.h"
#include "ArmRetractCommand.h"
#include "ArmExtendCommand.h"
#include "AutoDriveCommand.h"

class AutoContainersFromStepCommandGroup: public CommandGroup
{
public:
	AutoContainersFromStepCommandGroup(){
		AddSequential(new ArmGoToPositionCommand(ARM_PIVOT_POSITION_BOTTOM));
		AddSequential(new ArmExtendCommand());
		AddParallel(new ArmGripperCloseCommand());
		AddSequential(new WaitCommand(.25));
		AddSequential(new ArmRetractCommand());
		AddParallel(new ArmGripperOpenCommand());
		AddSequential(new WaitCommand(.25));
		AddSequential(new AutoDriveCommand(1,0,0,1.5));

		AddSequential(new ArmExtendCommand());
		AddParallel(new ArmGripperCloseCommand());
		AddSequential(new WaitCommand(.25));
		AddSequential(new ArmRetractCommand());
		AddParallel(new ArmGripperOpenCommand());
		AddSequential(new WaitCommand(.25));
		AddSequential(new AutoDriveCommand(1,0,0,1.5));

		AddSequential(new ArmExtendCommand());
		AddParallel(new ArmGripperCloseCommand());
		AddSequential(new WaitCommand(.25));
		AddSequential(new ArmRetractCommand());
		AddParallel(new ArmGripperOpenCommand());
		AddSequential(new WaitCommand(.25));
		AddSequential(new AutoDriveCommand(1,0,0,1.5));

		AddSequential(new ArmExtendCommand());
		AddParallel(new ArmGripperCloseCommand());
		AddSequential(new WaitCommand(.25));
		AddSequential(new ArmRetractCommand());
		AddSequential(new AutoDriveCommand(0,0,1,1.0));
	}
};

#endif
