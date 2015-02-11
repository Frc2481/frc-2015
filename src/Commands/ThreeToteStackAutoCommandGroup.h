#ifndef ThreeToteStackAutoCommandGroup_H
#define ThreeToteStackAutoCommandGroup_H

#include <Commands/PickUpToteCommand.h>
#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "AutoDriveCommand.h"
#include "UnloadToteStackCommand.h"
#include "AcquireToteCommand.h"
#include "AutoMoveRCOutOfWayCommand.h"
#include "WaitForToteCommand.h"
#include "ArmGoToPositionCommand.h"
#include "ArmGripperCloseCommand.h"



class ThreeToteStackAutoCommandGroup: public CommandGroup
{
public:
	ThreeToteStackAutoCommandGroup(){
		AddParallel(new ArmGripperCloseCommand());
		AddParallel(new ArmGoToPositionCommand(ARM_PIVOT_POSITION_TOP));
		AddParallel(new AcquireToteCommand());
		AddSequential(new WaitForToteCommand());
		AddSequential(new AutoMoveRCOutOfWayCommand());
		AddParallel(new AutoDriveCommand(0,1,0,.5));
		AddParallel(new AcquireToteCommand());
		AddSequential(new WaitForToteCommand());
		AddSequential(new AutoMoveRCOutOfWayCommand());
		AddParallel(new AutoDriveCommand(0,1,0,.5));
		AddParallel(new AcquireToteCommand());
		AddSequential(new WaitForToteCommand());
		AddSequential(new AutoDriveCommand(1,0,0,1.5));
		AddSequential(new UnloadToteStackCommand());
	}
};

#endif
