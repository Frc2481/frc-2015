#ifndef UnloadStackerManual_H
#define UnloadStackerManual_H

#include "../CommandBase.h"
#include "RobotParameters.h"
#include "WPILib.h"

class UnloadStackerManual: public CommandBase
{
private:
	double mPhi;
	double mHeight;
	double mTime;

	double mArmLength;
	double mWristLength;
	double mSpeed;

	int mToteCount;
public:
	UnloadStackerManual(){
		Requires(driveTrain);
		Requires(intake);
		Requires(arm);
		Requires(stacker);

		mArmLength = 58.22;
		mWristLength = 10.0;
		mSpeed = 23.58;
	}
	void Initialize(){
		driveTrain->SetFieldCentric(false);

		mToteCount = stacker->GetToteCount();
		mHeight = (2.0 + (12.1 * mToteCount) + 4.0); 				    //height at which you want to drop off the can

		double theta = asin(mHeight / mArmLength);

		mPhi = 90.0 - (theta * (180.0 / 3.14159265));                   //angle the shoulder needs to go to

		mTime = (mWristLength + (mArmLength * cos(theta))) / mSpeed;    //time that we need to take backing up

//		if (mToteCount < 5 && !arm->IsGripper()){        				//mechanically we can unload normally if we have 5 or more tote's
//			arm->SetPivotArmAbs(mPhi);					 				//sets setpoint for the shoulder
//			SetTimeout(mTime + TimeSinceInitialized());
//		}
	}
	void Execute(){
//		if(mToteCount < 5 && !arm->IsGripper()){
//			intake->TurnOnReverse();
//			if(!IsTimedOut()){
//				driveTrain->Crab(0,.3,0);
//			}
//			else{
//				driveTrain->Crab(0,0,0);    //stopping the drivetrain
//				if(arm->IsArmOnTarget()){
//					arm->OpenGripper();
//				}
//			}
//		}
//		else{
			arm->OpenGripper();
			intake->TurnOnReverse();
			driveTrain->Crab(0,.2,0);   //!!this relies on boost being false
//		}
	}

	bool IsFinished(){
		return false;
	}
	void End(){
		stacker->ResetToteCount();
		intake->TurnOff();
		driveTrain->Crab(0,0,0);
	}
	void Interrupted(){
		End();
	}
};

#endif
