#ifndef ShortenFishingPolesCommand_H
#define ShortenFishingPolesCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ShortenFishingPolesCommand: public CommandBase
{
public:
	ShortenFishingPolesCommand(){}
	void Initialize(){
		fishingPoles->Shorten();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
