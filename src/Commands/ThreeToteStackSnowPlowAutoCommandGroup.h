#ifndef ThreeToteStackSnowPlowAutoCommandGroup_H
#define ThreeToteStackSnowPlowAutoCommandGroup_H

#include "Commands/PickUpToteCommand.h"
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
#include "DriveTrainSetGyroOffsetCommand.h"
#include "DriveTrainWaitForHeading.h"
#include "RotateToAngle.h"
#include "ToggleFieldCentricCommand.h"
#include "SetFieldCentricCommand.h"
#include "DriveTrainDisableGyroCorrectionCommand.h"

#define DRIVE_FORWARD_PLOW -.6
#define DRIVE_TO_NEXT_TOTE -.3
#define DRIVE_FAST_TO_NEXT_TOTE -1
#define PLOW_DRIVE_TIME .6
#define FAST_DRIVE_TIME .25
#define PLOW_ANGLE 45

#define DRIVE_FORWARD_PLOW_2 -.6
#define DRIVE_TO_NEXT_TOTE_2 -.3
#define DRIVE_FAST_TO_NEXT_TOTE_2 -1
#define PLOW_DRIVE_TIME_2 .6
#define FAST_DRIVE_TIME_2 .3
#define PLOW_ANGLE_2 45

#define RUSH_STAGE_1_SPEED .8
#define RUSH_STAGE_1_TIME 1.75
#define RUSH_STAGE_2_SPEED .2
#define RUSH_STAGE_2_TIME .1

class ThreeToteStackSnowPlowAutoCommandGroup: public CommandGroup
{
public:
	ThreeToteStackSnowPlowAutoCommandGroup(){

		AddSequential(new DriveTrainZeroYaw());
		AddSequential(new DriveTrainEnableGyroCorrectionCommand());
		AddParallel(new StackerGoToTopCommand());
		AddSequential(new WaitCommand(.5));

		AddSequential(new DriveTrainSetGyroOffsetCommand(PLOW_ANGLE));
		AddParallel(new IntakeTurnOnLeftReverse());
		AddSequential(new DriveTrainWaitForHeading(PLOW_ANGLE));
		AddSequential(new AutoDriveCommand(DRIVE_FORWARD_PLOW,DRIVE_FORWARD_PLOW,0,PLOW_DRIVE_TIME));
//		AddSequential(new AutoDriveCommand(DRIVE_FORWARD_PLOW*.819,DRIVE_FORWARD_PLOW*.574,0,PLOW_DRIVE_TIME));
		AddParallel(new DriveTrainSetGyroOffsetCommand(0));
		AddParallel(new AcquireToteAutoCommandGroup());
		AddSequential(new DriveTrainWaitForHeading(0));
		AddSequential(new AutoDriveCommand(0,-.1,0,.01));
		AddSequential(new AutoDriveCommand(0,DRIVE_FAST_TO_NEXT_TOTE,0,FAST_DRIVE_TIME));
		AddParallel(new AutoDriveCommand(0,DRIVE_TO_NEXT_TOTE,0));
		AddSequential(new WaitForToteCommand());
		AddParallel(new AutoDriveCommand(0,0,0));
		AddSequential(new IntakeTurnOff());

//		AddSequential(new PickUpToteCommand());
		AddSequential(new IncrementToteCountCommand());
		AddSequential(new StackerGoToBottomCommand());
		AddParallel(new StackerGoToNextPositionCommand());
		AddSequential(new WaitCommand(.3));
		//AddSequential(new WaitForToteCountToIncreaseCommand());

		AddParallel(new IntakeTurnOnLeftReverse());
		AddSequential(new DriveTrainSetGyroOffsetCommand(PLOW_ANGLE_2));

		AddSequential(new DriveTrainWaitForHeading(PLOW_ANGLE_2));
		AddSequential(new AutoDriveCommand(DRIVE_FORWARD_PLOW_2,DRIVE_FORWARD_PLOW_2,0,PLOW_DRIVE_TIME_2));
//		AddSequential(new AutoDriveCommand(DRIVE_FORWARD_PLOW*.819,DRIVE_FORWARD_PLOW*.574,0,PLOW_DRIVE_TIME));
		AddParallel(new DriveTrainSetGyroOffsetCommand(0));
//		AddParallel(new AcquireToteAutoCommandGroup());
		AddSequential(new DriveTrainWaitForHeading(0));
		AddSequential(new AutoDriveCommand(0,-.1,0,.01));
		AddSequential(new AutoDriveCommand(0,DRIVE_FAST_TO_NEXT_TOTE_2,0,FAST_DRIVE_TIME_2));
		AddParallel(new AcquireToteAutoCommandGroup());
		AddParallel(new AutoDriveCommand(0,DRIVE_TO_NEXT_TOTE_2,0));
		AddSequential(new WaitForToteCommand());
		AddParallel(new AutoDriveCommand(0,0,0));

		AddParallel(new StackerGoToBottomCommand(true));
		AddSequential(new AutoDriveCommand(RUSH_STAGE_1_SPEED,0,0,RUSH_STAGE_1_TIME));
		AddSequential(new AutoDriveCommand(RUSH_STAGE_2_SPEED,0,0,RUSH_STAGE_2_TIME));

		AddSequential(new UnloadToteStackCommandGroup(true));
	}
};

#endif
