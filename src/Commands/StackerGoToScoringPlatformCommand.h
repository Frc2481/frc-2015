#ifndef STACKER_GO_TO_SCORING_PLATFORM_COMMAND_H
#define STACKER_GO_TO_SCORING_PLATFORM_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToScoringPlatformCommand: public CommandBase
{
public:
	StackerGoToScoringPlatformCommand() : CommandBase() {
	}
	void Initialize(){
		CommandBase::stacker->SetPosition(2.5f);
	}
	void Execute() {}
	bool IsFinished(){
		return CommandBase::stacker->OnTarget();
	}
	void End(){
		CommandBase::stacker->Stop();
	}
	void Interrupted(){
		End();
	}
};

#endif
