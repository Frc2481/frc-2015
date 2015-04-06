#ifndef StackerAutoZero_H
#define StackerAutoZero_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerAutoZero: public CommandBase
{
private:
	bool mFirst;
public:
	StackerAutoZero(){}
	void Initialize(){
		SetTimeout(2);
		mFirst = true;
	}
	void Execute(){
		if(IsTimedOut() && mFirst){
			stacker->Reset();
			mFirst = false;
		}
	}
	bool IsFinished(){
		return false;
	}
	void End(){}
	void Interrupted(){}
};

#endif
