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
#include "UnloadToteStackManualCommandGroup.h"



class ThreeToteStackAutoCommandGroup: public CommandGroup
{
public:
	ThreeToteStackAutoCommandGroup(){
//		AddParallel(new ArmGripperCloseCommand());
		AddParallel(new ArmShoulderToSetPoint(2));
//
		AddParallel(new AutoDriveCommand(0,-.3,0,1.5));
		AddSequential(new AcquireToteCommand());
		AddParallel(new AutoDriveCommand(0,-.5,0));
		AddSequential(new AcquireToteCommand());

		//AddSequential(new AutoDriveCommand(0,.5,0,.25,.1));

		//Reverse
		AddSequential(new AutoDriveCommand(0,.1,0,.15));
		AddSequential(new WaitCommand(.1));
		AddSequential(new AutoDriveCommand(0,.5,0,.25));
		AddSequential(new WaitCommand(.25));

		//Strafe Right
		AddSequential(new AutoDriveCommand(.1,0,0,.15));
		AddSequential(new WaitCommand(.1));
		AddSequential(new AutoDriveCommand(.5,0,0,.75));
		AddSequential(new WaitCommand(.25));

		//Drive Forward
		AddSequential(new AutoDriveCommand(0,-.1,0,.15));
		AddSequential(new WaitCommand(.1));
		AddSequential(new AutoDriveCommand(0,-.5,0,1));
		AddSequential(new WaitCommand(.25));

		//Strafe Left
		AddSequential(new AutoDriveCommand(-.1,0,0,.15));
		AddSequential(new WaitCommand(.1));
		AddSequential(new AutoDriveCommand(-.5,0,0,.95));
		AddSequential(new WaitCommand(.25));

		//Drive Forward
		AddSequential(new AutoDriveCommand(0,-.1,.15));
		AddSequential(new WaitCommand(.1));
		AddParallel(new AutoDriveCommand(0,-.5,0));
		AddSequential(new WaitCommand(.25));


		AddSequential(new AcquireToteCommand());
		AddSequential(new AutoDriveCommand(.5,0,0,3));

		AddSequential(new UnloadToteStackCommandGroup());

//		AddSequential(new WaitForToteCommand());
//		AddParallel(new AutoDriveCommand(0,-.5,0,2.5));
		//AddSequential(new AcquireToteCommand());
		//AddSequential(new WaitForToteCommand());
//		AddSequential(new AutoMoveRCOutOfWayCommand());
//		AddParallel(new AutoDriveCommand(0,1,0,.5));
//		AddParallel(new AcquireToteCommand());
//		AddSequential(new WaitForToteCommand());
//		AddSequential(new AutoDriveCommand(1,0,0,1.5));
//		AddSequential(new UnloadToteStackCommand());
	}
};

#endif
