#ifndef TripleAcquireToteCommandGroup_H
#define TripleAcquireToteCommandGroup_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

class TripleAcquireToteCommandGroup: public CommandGroup
{
public:
	TripleAcquireToteCommandGroup(){
		AddSequential(new AcquireToteCommand());
		AddSequential(new AcquireToteCommand());
		AddSequential(new AcquireToteCommand());
	}
};

#endif
