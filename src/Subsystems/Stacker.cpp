#include "Stacker.h"
#include "RobotParameters.h"
#include "../RobotMap.h"

Stacker::Stacker() :
		Subsystem("Stacker")
{
	mRightLift = new Lift2481(9, 10, 11, .005, .001, 0, 0);
	mLeftLift = new Lift2481(10, 3, 4, .1, 0, 0, 5);

}

void Stacker::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Stacker::Reset() {
	mRightLift->Reset();
	mLeftLift->Reset();
}

bool Stacker::OnTarget() {
	return mRightLift->OnTarget() && mLeftLift->OnTarget();
}

void Stacker::SetPosition(float pos) {
	pos *= 2000;
	mRightLift->SetDesiredPostion(pos);
	mLeftLift->SetDesiredPostion(pos);
}

void Stacker::PeriodicUpdate() {
	mRightLift->PeriodicUpdate();
	mLeftLift->PeriodicUpdate();

#ifdef DEBUGGING
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
#endif
}

void Stacker::Stop(){
	mRightLift->Stop();
	mLeftLift->Stop();
}
bool Stacker::IsResetting(){
	return mRightLift->IsResetting() || mLeftLift->IsResetting();
}
