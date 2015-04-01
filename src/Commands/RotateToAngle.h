/*
 * RotateToAngle.h
 *
 *  Created on: Jan 16, 2015
 *      Author: thomasSpeciale
 */

#ifndef SRC_COMMANDS_ROTATETOANGLE_H_
#define SRC_COMMANDS_ROTATETOANGLE_H_

#include "../CommandBase.h"
#include "WPILib.h"

class RotateToAngle: public CommandBase
{
private:
	class PIDRotate : public PIDOutput{

		private:
			double value;

		public:
			PIDRotate(){
				value = 0.00;
			}

			float getValue (){
				return value;
			}

			void PIDWrite (float output){
				value = output;
			}
		};
	float mAngle;
	PIDRotate* mRotate;
	PIDController* mTurnController;
	bool mOnTarget;
public:
	RotateToAngle(float angle)
		: 	mAngle(angle),
			mRotate(new PIDRotate()),
			mTurnController(new PIDController(0.009f,0.0001,0.0f, driveTrain->GetIMU(), mRotate)),
			mOnTarget(false){
		Requires(driveTrain);
		mTurnController->SetOutputRange(-.5,.5);
		mTurnController->SetInputRange(-180, 180);
		mTurnController->SetContinuous(true);
		mTurnController->SetAbsoluteTolerance(2);
	}
	void Initialize(){
		mOnTarget = false;
		driveTrain->SetBrake(true);
		mTurnController->SetSetpoint(mAngle);
		mTurnController->Enable();
		SetTimeout(3);
	}
	void Execute(){
		driveTrain->Crab(0.0,0.0,mRotate->getValue());

		if (mTurnController->OnTarget() && !mOnTarget) {
			mOnTarget = true;
			mTurnController->Disable();
			SetTimeout(TimeSinceInitialized() + .2);
		}
	}
	bool IsFinished(){
		return IsTimedOut();
	}
	void End(){
		driveTrain->SetBrake(false);
	}
	void Interrupted(){
		End();
	}
};



#endif /* SRC_COMMANDS_ROTATETOANGLE_H_ */
