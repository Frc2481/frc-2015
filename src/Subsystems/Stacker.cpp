#include "Stacker.h"
#include "../RobotParameters.h"
#include "../RobotMap.h"

Stacker::Stacker() :
		Subsystem("Stacker"), mToteCount(0), mLiftLastExtreme(Up)
{
	float p = Preferences::GetInstance()->GetFloat("STACKER_P", .0002);
	float i = Preferences::GetInstance()->GetFloat("STACKER_I", .00001);

	mRightLift = new Lift2481(9, 10, 11, p, i, 0, STACKER_RIGHT_BOTTOM_LIMIT, STACKER_RIGHT_TOP_LIMIT);
	mLeftLift = new Lift2481(10, 12, 13, p, i, 0, STACKER_LEFT_BOTTOM_LIMIT, STACKER_LEFT_TOP_LIMIT);
	mLiftLastExtreme = Down;

	mLeftLift->SetInverted(true);
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
	pos *= STACKER_TICKS_PER_INCH;

	float i = Preferences::GetInstance()->GetFloat("STACKER_I", 0);
	float p = Preferences::GetInstance()->GetFloat("STACKER_P", .0002);
	mRightLift->SetI(i);
	mRightLift->SetP(p);
	mLeftLift->SetI(i);
	mLeftLift->SetP(p);

	std::cout << "p: " << p << " i " << i << std::endl;


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
			(std::min(lpos,rpos) > (STACKER_POSITION_UP - (STACKER_TICKS_PER_INCH + 100)))){

		mLiftLastExtreme = Up;

		mToteCount++;
	}
	else if (mCounterState == Lowering &&
			mLiftLastExtreme == Up &&
			(std::max(lpos,rpos) > (STACKER_POSITION_DOWN + (STACKER_TICKS_PER_INCH + 100)))){

		mLiftLastExtreme = Down;
	}

	float error = fabs(mRightLift->GetCurrentPostion() - mRightLift->GetDesiredPostion());
	if (error > 500) {
		mRightLift->GetController()->ResetError();
		mLeftLift->GetController()->ResetError();
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
	SmartDashboard::PutData("stackerLeftController", (PIDController*)mLeftLift->GetController());
	SmartDashboard::PutData("stackerRightController", (PIDController*)mRightLift->GetController());
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
