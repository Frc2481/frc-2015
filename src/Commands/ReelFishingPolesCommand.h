#ifndef ReelFishingPolesCommand_H
#define ReelFishingPolesCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ReelFishingPolesCommand: public CommandBase
{
public:
	ReelFishingPolesCommand(){
		Requires(fishingPoles);
	}
	void Initialize(){
		fishingPoles->Reel();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
