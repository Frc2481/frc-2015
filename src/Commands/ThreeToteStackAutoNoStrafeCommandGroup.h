#ifndef ThreeToteStackAutoNoStrafeCommandGroup_H
#define ThreeToteStackAutoNoStrafeCommandGroup_H

#include <Commands/PickUpToteCommand.h>
#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "AutoDriveCommand.h"
#include "UnloadToteStackCommand.h"
#include "AcquireToteAutoCommandGroup.h"
#include "AutoMoveRCOutOfWayCommand.h"
#include "WaitForToteCommand.h"
#include "ArmGoToPositionCommand.h"
#include "ArmGripperCloseCommand.h"
#include "UnloadToteStackManualCommandGroup.h"
#include "TripleAcquireToteCommandGroup.h"
#include "DriveTrainEnableGyroCorrectionCommand.h"
#include "DriveTrainZeroYaw.h"
#include "IntakeTurnOnReverse.h"



class ThreeToteStackAutoNoStrafeCommandGroup: public CommandGroup
{
public:
	ThreeToteStackAutoNoStrafeCommandGroup(){
		//AddParallel(new TripleAcquireToteCommandGroup());
		//AddParallel(new ArmShoulderToSetPoint(2));
		AddSequential(new DriveTrainZeroYaw());
		AddSequential(new DriveTrainEnableGyroCorrectionCommand());

		//AddSequential(new AutoDriveCommand(0,-.1,0,.25));
//		AddSequential(new AutoDriveCommand(0,-.4,0,10));
//		return;

		AddParallel(new AcquireToteAutoCommandGroup());
		AddSequential(new AutoDriveCommand(0,-.4,.3));
		AddSequential(new AutoDriveCommand(0,-.2,0));
		AddSequential(new WaitForToteCommand());
		AddSequential(new WaitCommand(.25));

		/* FIRST CAN */

		//Drive Forward
		AddParallel(new IntakeTurnOnReverse());
		AddSequential(new AutoDriveCommand(0,-.11,0,.25));
		AddSequential(new AutoDriveCommand(0,-.5,0,.6));
		/* END FIRST CAN */

		AddParallel(new AcquireToteAutoCommandGroup());
		AddSequential(new AutoDriveCommand(0,-.6,0,.7));

		AddSequential(new AutoDriveCommand(0,-.2,0));
		AddSequential(new WaitForToteCommand());
		AddSequential(new WaitCommand(.25));
		//AddParallel(new AutoDriveCommand(0,-.5,0));

		//Reverse
//		AddSequential(new AutoDriveCommand(0,.11,0,.25));
//		AddSequential(new WaitCommand(.1));
//		AddSequential(new AutoDriveCommand(0,.5,0,.4));
//		AddSequential(new WaitCommand(.25));

		/* Second CAN */

		//Drive Forward
		AddParallel(new IntakeTurnOnReverse());
		AddSequential(new AutoDriveCommand(0,-.11,0,.25));
		AddSequential(new AutoDriveCommand(0,-.5,0,.6));
		/* END Second CAN */

		//Drive Forward
		AddSequential(new AutoDriveCommand(0,-.11,0,.25));
		AddParallel(new AutoDriveCommand(0,-.5,0));

		AddParallel(new AcquireToteAutoCommandGroup());
		AddSequential(new WaitForToteCommand());
		AddParallel(new StackerGoToBottomCommand(true));
		AddSequential(new AutoDriveCommand(.8,0,0,1.8));
		AddSequential(new AutoDriveCommand(.2,0,0,.1));

		AddSequential(new UnloadToteStackCommandGroup(true));

	}
};

#endif
