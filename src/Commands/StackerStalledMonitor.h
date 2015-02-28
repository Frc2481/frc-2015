#ifndef StackerStalledMonitor_H
#define StackerStalledMonitor_H

#include "../CommandBase.h"
#include "Components/PersistedSettings.h"
#include "WPILib.h"

class StackerStalledMonitor: public CommandBase
{
private:
	bool mEnabled;
public:
	StackerStalledMonitor(){
		mEnabled = false;
	}
	void Initialize(){}
	void Execute(){
		if(stacker->IsEnabled() && !mEnabled){
			SetTimeout(3 + TimeSinceInitialized());
			mEnabled = true;
		}
		if(IsTimedOut() && mEnabled){
			if (!mEnabled){
				PersistedSettings::GetInstance().Set("STACKER_STALL_COUNT",
						PersistedSettings::GetInstance().Get("STACKER_STALL_COUNT", 0) + 1);
				SmartDashboard::PutBoolean("Stacker Stalled", IsTimedOut());
			}
			stacker->Disable();
			mEnabled = false;
		}
	}
	bool IsFinished(){}
	void End(){}
	void Interrupted(){}
};

#endif
