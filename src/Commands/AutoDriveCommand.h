#ifndef AutoDriveCommand_H
#define AutoDriveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class AutoDriveCommand: public CommandBase
{
private:
	double mX;
	double mY;
	double mTwist;
	bool mTimeoutSet;

public:
	AutoDriveCommand(double x, double y, double twist, double timeout = 0)
			: mX(x), mY(y), mTwist(twist){
		Requires(driveTrain);
		if (timeout > 0){
			SetTimeout(timeout);
			mTimeoutSet = true;
		}
		else {
			mTimeoutSet = false;
		}
	}
	void Initialize(){
//		CommandBase::driveTrain->Crab(mX,mY,mTwist);
	}
	void Execute(){
		CommandBase::driveTrain->Crab(mX,mY,mTwist);
	}
	bool IsFinished(){
		return IsTimedOut() || !mTimeoutSet;
	}
	void End(){
		if (mTimeoutSet){
			CommandBase::driveTrain->Stop();
		}
	}
	void Interrupted(){
		End();
	}
};

#endif
