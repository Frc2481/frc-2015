#ifndef AutoMoveRCOutOfWayCommand_H
#define AutoMoveRCOutOfWayCommand_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class AutoMoveRCOutOfWayCommand: public CommandGroup
{
public:
	AutoMoveRCOutOfWayCommand(){
		AddSequential(new AutoDriveCommand(-1,0,0,.5));
		AddSequential(new AutoDriveCommand(0,1,0,1.5));
		AddSequential(new AutoDriveCommand(1,0,0,.5));
	}
};

#endif
