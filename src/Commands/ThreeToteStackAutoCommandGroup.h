#ifndef ThreeToteStackAutoCommandGroup_H
#define ThreeToteStackAutoCommandGroup_H

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
#include "UnloadToteStackCommandGroup.h"
#include "TripleAcquireToteCommandGroup.h"
#include "DriveTrainEnableGyroCorrectionCommand.h"
#include "DriveTrainZeroYaw.h"
#include "IntakeTurnOnReverse.h"



class ThreeToteStackAutoCommandGroup: public CommandGroup
{
public:
	ThreeToteStackAutoCommandGroup(){
		//AddParallel(new TripleAcquireToteCommandGroup());
		//AddParallel(new ArmShoulderToSetPoint(2));
		AddSequential(new DriveTrainZeroYaw());
		AddSequential(new DriveTrainEnableGyroCorrectionCommand());

		//AddSequential(new AutoDriveCommand(0,-.1,0,.25));
//		AddSequential(new AutoDriveCommand(0,-.4,0,10));
//		return;

		AddSequential(new StackerGoToTopCommand());

		/* FIRST CAN */
		//Strafe Right
		AddSequential(new AutoDriveCommand(.11,0,0,.25));
		AddSequential(new AutoDriveCommand(.5,0,0,.6));

		//Drive Forward
		AddSequential(new AutoDriveCommand(0,-.11,0,.25));
		AddParallel(new IntakeTurnOnLeftReverse());
		AddSequential(new AutoDriveCommand(0,-.5,0,.6));

		//Strafe Left
		AddSequential(new AutoDriveCommand(-.11,0,0,.25));
		AddSequential(new AutoDriveCommand(-.5,0,0,.65));
		/* END FIRST CAN */

		AddParallel(new AcquireToteAutoCommandGroup());
		AddSequential(new AutoDriveCommand(0,-.6,0,.9));

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
		//Strafe Right
		AddSequential(new AutoDriveCommand(.11,0,0,.25));
		AddSequential(new AutoDriveCommand(.5,0,0,.65));

		//Drive Forward
		AddSequential(new AutoDriveCommand(0,-.11,0,.25));
		AddParallel(new IntakeTurnOnLeftReverse());
		AddSequential(new AutoDriveCommand(0,-.5,0,.6));

		//Strafe Left
		AddSequential(new AutoDriveCommand(-.11,0,0,.25));
		AddSequential(new AutoDriveCommand(-.5,0,0,.7));
		/* END Second CAN */

		//Drive Forward
		AddParallel(new AcquireToteAutoCommandGroup());
		AddSequential(new AutoDriveCommand(0,-.6,0,1.1));
		AddSequential(new AutoDriveCommand(0,-.2,0));
		AddSequential(new WaitForToteCommand());

		AddParallel(new StackerGoToBottomCommand(true));
		AddSequential(new AutoDriveCommand(.8,0,0,1.65));
		AddSequential(new AutoDriveCommand(.2,0,0,.1));

		AddSequential(new UnloadToteStackCommandGroup(true));

	}
};

#endif
