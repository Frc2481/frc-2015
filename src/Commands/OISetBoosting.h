#ifndef OISetBoosting_H
#define OISetBoosting_H

#include "../CommandBase.h"
#include "WPILib.h"

class OISetBoosting: public CommandBase
{
public:
	OISetBoosting(){}
	void Initialize(){
		oi->SetBoosting(true);
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		oi->SetBoosting(false);
	}
	void Interrupted(){
		End();
	}
};

#endif
