#ifndef CastFishingPolesCommand_H
#define CastFishingPolesCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class CastFishingPolesCommand: public CommandBase
{
public:
	CastFishingPolesCommand(){
		Requires(fishingPoles);
	}
	void Initialize(){
		fishingPoles->Cast();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
