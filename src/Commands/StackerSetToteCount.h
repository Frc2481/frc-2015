#ifndef StackersetToteCount_H
#define StackersetToteCount_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerSetToteCount: public CommandBase
{
protected:
	int mToteCount;
public:
	StackerSetToteCount(int toteCount)
		: mToteCount(toteCount){
	}
	void Initialize(){
		SetTimeout(.75);
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		if (!IsTimedOut()) {
			stacker->setDesiredToteCount(mToteCount);
		} else {
			stacker->SetToteCount(mToteCount);
		}
	}
	void Interrupted(){
		End();
	}
};

#endif
