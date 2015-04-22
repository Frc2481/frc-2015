#ifndef ThreeToteStackNoStrafeAutoCommandGroup_H
#define ThreeToteStackNoStrafeAutoCommandGroup_H

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



class ThreeToteStackNoStrafeAutoCommandGroup: public CommandGroup
{
public:
	ThreeToteStackNoStrafeAutoCommandGroup(){
		//AddParallel(new TripleAcquireToteCommandGroup());
		//AddParallel(new ArmShoulderToSetPoint(2));
		AddSequential(new DriveTrainZeroYaw());
		AddSequential(new DriveTrainEnableGyroCorrectionCommand());

		//AddSequential(new AutoDriveCommand(0,-.1,0,.25));
//		AddSequential(new AutoDriveCommand(0,-.4,0,10));
//		return;

		AddParallel(new StackerGoToTopCommand()); //Previously sequential
		AddSequential(new WaitCommand(0.19));

		/* FIRST CAN */
		AddParallel(new IntakeTurnOnLeftReverse());

		//Strafe Right
		AddSequential(new AutoDriveCommand(.11,0,0,.25));
		AddSequential(new AutoDriveCommand(.5,0,0,.6));

		//Drive Forward
		AddSequential(new AutoDriveCommand(0,-.11,0,.25));
		AddSequential(new AutoDriveCommand(0,-.5,0,.6));

		//Strafe Left
		AddSequential(new AutoDriveCommand(-.11,0,0,.25));
		AddSequential(new AutoDriveCommand(-.5,0,0,.645));
		/* END FIRST CAN */

		AddParallel(new AcquireToteAutoCommandGroup());
		AddSequential(new AutoDriveCommand(0,-.6,0,.75));

		AddSequential(new AutoDriveCommand(0,-.2,0));
		AddSequential(new WaitForToteCommand());
		AddSequential(new WaitCommand(.4));
		//AddParallel(new AutoDriveCommand(0,-.5,0));

		//Reverse
//		AddSequential(new AutoDriveCommand(0,.11,0,.25));
//		AddSequential(new WaitCommand(.1));
//		AddSequential(new AutoDriveCommand(0,.5,0,.4));
//		AddSequential(new WaitCommand(.25));

		/* Second CAN */
		AddParallel(new IntakeTurnOnLeftReverse());

		//Strafe Right
		AddSequential(new AutoDriveCommand(.11,0,0,.25));
		AddSequential(new AutoDriveCommand(.5,0,0,.645));

		//Drive Forward
		AddSequential(new AutoDriveCommand(0,-.11,0,.25));
		AddSequential(new AutoDriveCommand(0,-.5,0,.9));

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
		AddSequential(new AutoDriveCommand(.8,0,0,1.5)); //Previous -.3 y
		AddSequential(new AutoDriveCommand(.2,0,0,.1)); //Previous -.2 y

		AddSequential(new UnloadToteStackCommandGroup(true));

	}
};

#endif
