#ifndef LengthenFishingPolesCommand_H
#define LengthenFishingPolesCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class LengthenFishingPolesCommand: public CommandBase
{
public:
	LengthenFishingPolesCommand(){}
	void Initialize(){
		fishingPoles->Lengthen();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
