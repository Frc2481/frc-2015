#include "Stacker.h"
#include "../RobotParameters.h"
#include "../RobotMap.h"

Stacker::Stacker() :
		Subsystem("Stacker"), mToteCount(0), mLiftLastExtreme(Up)
{
	mRightLift = new Lift2481(9, 10, 11, .005, .001, 0, 0);
	mLeftLift = new Lift2481(10, 3, 4, .1, 0, 0, 5);
	mLiftLastExtreme = Down;
}

void Stacker::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Stacker::Reset() {
	mRightLift->Reset();
	mLeftLift->Reset();
	mLiftLastExtreme = Down;
}

bool Stacker::OnTarget() {
	return mRightLift->OnTarget() && mLeftLift->OnTarget();
}

void Stacker::SetPosition(float pos) {
	pos *= 100;
	mRightLift->SetDesiredPostion(pos);
	mLeftLift->SetDesiredPostion(pos);
}

void Stacker::PeriodicUpdate() {
	mRightLift->PeriodicUpdate();
	mLeftLift->PeriodicUpdate();
	float lpos = mLeftLift->GetCurrentPostion();
	float rpos = mRightLift->GetCurrentPostion();
	float ldpos = mLeftLift->GetDesiredPostion();
	float rdpos = mRightLift->GetDesiredPostion();

	if (lpos < ldpos || rpos < rdpos){
		mCounterState = Raising;
	}
	else if (lpos > ldpos || rpos > rdpos){
		mCounterState = Lowering;
	}

	if (mCounterState == Raising &&
			mLiftLastExtreme == Down &&
			(std::min(lpos,rpos) > (STACKER_POSITION_UP - 100))){

		mLiftLastExtreme = Up;

		mToteCount++;
	}
	else if (mCounterState == Lowering &&
			mLiftLastExtreme == Up &&
			(std::max(lpos,rpos) > (STACKER_POSITION_DOWN + 100))){

		mLiftLastExtreme = Down;
	}



#ifdef DEBUGGING
	SmartDashboard::PutNumber("ToteCount", mToteCount);
	SmartDashboard::PutNumber("stackerLeftPosition", mLeftLift->GetDesiredPostion());
	SmartDashboard::PutNumber("stackerRightPosition", mRightLift->GetDesiredPostion());
	SmartDashboard::PutBoolean("stackerLeftOnTarget", mLeftLift->OnTarget());
	SmartDashboard::PutBoolean("stackerRightOnTarget", mRightLift->OnTarget());
	SmartDashboard::PutBoolean("stackerLeftResetting", mLeftLift->IsResetting());
	SmartDashboard::PutBoolean("stackerRightResetting", mRightLift->IsResetting());
	SmartDashboard::PutNumber("stackerLeftCurrentPosition", mLeftLift->GetCurrentPostion());
	SmartDashboard::PutNumber("stackerRightCurrentPosition", mRightLift->GetCurrentPostion());
	SmartDashboard::PutData("stackerLeftController", mLeftLift->GetController());
	SmartDashboard::PutData("stackerRightController", mRightLift->GetController());
	SmartDashboard::PutNumber("RightStackerState", mRightLift->GetLiftState());
	SmartDashboard::PutNumber("LeftStackerState", mLeftLift->GetLiftState());
#endif
}

void Stacker::Stop(){
	mRightLift->Stop();
	mLeftLift->Stop();
}

int Stacker::GetToteCount() const {
	return mToteCount;
}

void Stacker::SetToteCount(int toteCount) {
	mToteCount = toteCount;
}

bool Stacker::IsResetting(){
	return mRightLift->IsResetting() || mLeftLift->IsResetting();
}

void Stacker::IncrementToteCount() {
	mToteCount++;
}

void Stacker::DecrementToteCount() {
	mToteCount--;
}

void Stacker::SetFeedbackEnable(StackerLiftID id, bool state) {
	if(id == RIGHT){
		mRightLift->SetFeedbackState(state);
	}
	if(id == LEFT){
		mLeftLift->SetFeedbackState(state);
	}

}
