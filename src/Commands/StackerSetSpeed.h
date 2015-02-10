#ifndef StackerSetSpeed_H
#define StackerSetSpeed_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerSetSpeed: public CommandBase
{
private:
	float mSpeed;

public:
	StackerSetSpeed(float speed){
		mSpeed = speed;
	}
	void Initialize(){}
	void Execute(){
		CommandBase::stacker->Set(mSpeed);

	}
	bool IsFinished(){
		return false;
	}
	void End(){
		CommandBase::stacker->Set(0);
	}
	void Interrupted(){
		End();
	}
};

#endif
