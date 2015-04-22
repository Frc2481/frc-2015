#ifndef FishingPoleAutoCommandGroup_H
#define FishingPoleAutoCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CastFishingPolesCommand.h"
#include "AutoDriveCommand.h"
#include "ReelFishingPolesCommand.h"
#include "ShortenFishingPolesCommand.h"

class FishingPoleAutoCommandGroup: public CommandGroup
{
public:
	FishingPoleAutoCommandGroup() {
		AddParallel(new CastFishingPolesCommand());
		//AddSequential(new DriveTrainZeroYaw());
		//AddSequential(new DriveTrainEnableGyroCorrectionCommand());
		AddSequential(new WaitCommand(.225));
		AddParallel(new AutoDriveCommand(0,-1,0,1.5));
		AddSequential(new WaitCommand(.1));
		AddParallel(new ShortenFishingPolesCommand());
		AddSequential(new WaitCommand(.3));
		AddSequential(new ReelFishingPolesCommand());
		AddSequential(new WaitCommand(1.2));
		AddSequential(new AutoDriveCommand(0,0,-.2,1.5));
//		AddSequential(new WaitCommand(.025));
//		AddSequential(new AutoDriveCommand(0,-1,0,.3));
//		AddParallel(new ReelFishingPolesCommand());
//		AddSequential(new AutoDriveCommand(0,-.2,0,1));
//		AddSequential(new WaitCommand(.2));
//		AddSequential(new AutoDriveCommand(.11,0,0,.25));
	}
};

#endif
