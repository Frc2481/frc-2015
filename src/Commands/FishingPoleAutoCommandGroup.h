#ifndef FishingPoleAutoCommandGroup_H
#define FishingPoleAutoCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"
#include "CastFishingPolesCommand.h"
#include "AutoDriveCommand.h"
#include "ReelFishingPolesCommand.h"

class FishingPoleAutoCommandGroup: public CommandGroup
{
public:
	FishingPoleAutoCommandGroup(){
		AddSequential(new CastFishingPolesCommand());
		AddSequential(new WaitCommand(.5));
		AddSequential(new ReelFishingPolesCommand());
		AddSequential(new WaitCommand(.05));
		AddSequential(new AutoDriveCommand(0,-1,0,.3));
//		AddSequential(new AutoDriveCommand(0,-1,0,.3));
//		AddParallel(new ReelFishingPolesCommand());
//		AddSequential(new AutoDriveCommand(0,-.2,0,1));
//		AddSequential(new WaitCommand(.2));
//		AddSequential(new AutoDriveCommand(.11,0,0,.25));
	}
};

#endif
