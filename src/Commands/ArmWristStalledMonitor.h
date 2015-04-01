#ifndef ArmWristStalledMonitor_H
#define ArmWristStalledMonitor_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmWristStalledMonitor: public CommandBase
{
private:
	bool mWristResetting;
public:
	ArmWristStalledMonitor(){
		mWristResetting = true;
	}
	void Initialize(){}
	void Execute(){
		if(arm->GetStalled() && !mWristResetting){
			SetTimeout(WRIST_STALL_TIMEOUT + TimeSinceInitialized());
			mWristResetting = true;
		}
		if(IsTimedOut() && mWristResetting){
			arm->SetStalled(false);
			mWristResetting = false;
		}
	}
	bool IsFinished(){
		return false;
	}
	void End(){}
	void Interrupted(){}
};

#endif
