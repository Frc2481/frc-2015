#ifndef RemoveRCFromStepCommand_H
#define RemoveRCFromStepCommand_H

#include "Commands/CommandGroup.h"
#include "WPILib.h"

#include "ArmGoToPositionCommand.h"
#include "ArmGripperCloseCommand.h"
#include "ArmGripperOpenCommand.h"
#include "ArmExtendCommand.h"
#include "ArmRetractCommand.h"

class RemoveRCFromStepCommand: public CommandGroup
{
public:
	RemoveRCFromStepCommand() {
		//AddSequential(new ArmGoToPositionCommand(80));
		AddSequential(new ArmGripperOpenCommand());
		AddSequential(new ArmExtendCommand());
		AddSequential(new WaitCommand(1));
		AddSequential(new ArmGripperCloseCommand());
		AddSequential(new WaitCommand(.25));
		AddSequential(new ArmGoToPositionCommand(75));
		AddSequential(new ArmRetractCommand());
		AddSequential(new WaitCommand(.7));
		AddSequential(new ArmGripperOpenCommand());


	}
};

#endif
