#include "Stacker.h"
#include "../RobotParameters.h"
#include "../RobotMap.h"

Stacker::Stacker() :
		Subsystem("Stacker"),
		mToteCount(0),
		mDesiredToteCount(6)
{
	float p = PersistedSettings::GetInstance().Get("STACKER_P", 0.0002);
	float i = PersistedSettings::GetInstance().Get("STACKER_I", 0.0002); //changed from .00005
	float d = 0; //changed from 0.0002

	mRightLift = new Lift2481(
			RIGHT_STACKER,
			STACKER_ENCODER_A,
			STACKER_ENCODER_B,
			p,
			i,
			d,
			STACKER_RIGHT_TOP_LIMIT,
			STACKER_RIGHT_BOTTOM_LIMIT,
			STACKER_BRAKE
		);
}

void Stacker::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Stacker::Reset() {
	mRightLift->Reset();
}

bool Stacker::OnTarget() {
	return mRightLift->OnTarget();
}

void Stacker::SetPosition(float pos, bool loaded) {
	pos *= STACKER_TICKS_PER_INCH;

	float i = PersistedSettings::GetInstance().Get("STACKER_I", .0002);
	float p = PersistedSettings::GetInstance().Get("STACKER_P", .0002);
	float d = PersistedSettings::GetInstance().Get("STACKER_D", .000001);

	mRightLift->SetI(loaded ? 0.0 : i);
	mRightLift->SetP(loaded ? 0.0003 : p);
	mRightLift->SetD(loaded ? 0.0 : d);

	mRightLift->SetDesiredPostion(pos);
}

float Stacker::GetPosition() {
	return mRightLift->GetCurrentPostion();
}

void Stacker::PeriodicUpdate() {
//	SmartDashboard::PutNumber("Stacker Current AVG Power", mRightLift->GetAverageCurrent() * mRightLift->GetAverageVoltage());

	mRightLift->PeriodicUpdate();

	float error = fabs(mRightLift->GetCurrentPostion() - mRightLift->GetDesiredPostion());
	if (error > 2000) {
		mRightLift->GetController()->ResetError();
	}

#ifdef DEBUGGING
	SmartDashboard::PutNumber("ToteCount", mToteCount);
	SmartDashboard::PutNumber("Desired Tote Count", mDesiredToteCount);
//	SmartDashboard::PutNumber("stackerRightPosition", mRightLift->GetDesiredPostion());
	SmartDashboard::PutBoolean("stackerRightOnTarget", mRightLift->OnTarget());
	SmartDashboard::PutBoolean("stackerRightResetting", mRightLift->IsResetting());
	SmartDashboard::PutNumber("stackerRightCurrentPosition", mRightLift->GetCurrentPostion());
	SmartDashboard::PutData("stackerRightController", (PIDController*)mRightLift->GetController());
//	SmartDashboard::PutNumber("RightStackerState", mRightLift->GetLiftState());
	SmartDashboard::PutBoolean("top limit", mRightLift->IsTopLimit());
	SmartDashboard::PutBoolean("Bottom Limit", mRightLift->IsBottomLimit());
#endif
}

int Stacker::GetToteCount() const {
	return mToteCount;
}

void Stacker::SetToteCount(int toteCount) {
	mToteCount = toteCount;
}

bool Stacker::IsResetting(){
	return mRightLift->IsResetting();
}

void Stacker::IncrementToteCount() {
	mToteCount++;
}

void Stacker::DecrementToteCount() {
	mToteCount--;
}

void Stacker::ResetToteCount() {
	mToteCount = 0;
}

void Stacker::Set(float output) {
	mRightLift->Set(output);
}

void Stacker::Disable(bool motor, bool brake){
	mRightLift->Disable(motor, brake);
}

void Stacker::Enable(bool motor) {
	mRightLift->Enable(motor);
}

bool Stacker::IsEnabled() {
	return mRightLift->GetController()->IsEnabled();
}

void Stacker::StackerManual(float yValue) {
	if (yValue < -0.2){
		mRightLift->Set(STACKER_DOWN_SPEED);
	}
	else if (yValue > 0.2){
		mRightLift->Set(STACKER_UP_SPEED);
	}
	else
		mRightLift->Set(0.0f);
}

int Stacker::getDesiredToteCount() const {
	return mDesiredToteCount;
}

void Stacker::setDesiredToteCount(int desiredToteCount) {
	mDesiredToteCount = desiredToteCount;
}
