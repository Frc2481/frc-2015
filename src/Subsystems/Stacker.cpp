#include "Stacker.h"
#include "../RobotParameters.h"
#include "../RobotMap.h"

Stacker::Stacker() :
		Subsystem("Stacker"), mToteCount(0), mDesiredToteCount(6), mLiftLastExtreme(Up), mMaxPower(0)
{
	float p = PersistedSettings::GetInstance().Get("STACKER_P", 0.0002);
	float i = PersistedSettings::GetInstance().Get("STACKER_I", 0.0002);
	printf ("%f %f \n", p, i);

	mRightLift = new Lift2481(RIGHT_STACKER, STACKER_ENCODER_A, STACKER_ENCODER_B, p, i, 0, STACKER_RIGHT_TOP_LIMIT, STACKER_RIGHT_BOTTOM_LIMIT, STACKER_BRAKE);
	mLiftLastExtreme = Down;
}

void Stacker::InitDefaultCommand()
{
	// Set the default command for a subsystem here.
	//SetDefaultCommand(new MySpecialCommand());
}

void Stacker::Reset() {
	mRightLift->Reset();
	mLiftLastExtreme = Down;
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
	SmartDashboard::PutNumber("Stacker Current AVG Power", mRightLift->GetAverageCurrent() * mRightLift->GetAverageVoltage());

	mRightLift->PeriodicUpdate();
	float rpos = mRightLift->GetCurrentPostion();
	float rdpos = mRightLift->GetDesiredPostion();

	if (rpos < rdpos){
		mCounterState = Raising;
	}
	else if (rpos > rdpos){
		mCounterState = Lowering;
	}

	if (mCounterState == Raising &&
			mLiftLastExtreme == Down &&
			(rpos > (STACKER_POSITION_UP - (STACKER_TICKS_PER_INCH + 100)))){

		mLiftLastExtreme = Up;
	}
	else if (mCounterState == Lowering &&
			mLiftLastExtreme == Up &&
			(rpos < (STACKER_POSITION_DOWN + (STACKER_TICKS_PER_INCH + 100)))){

		mLiftLastExtreme = Down;
	}

	float error = fabs(mRightLift->GetCurrentPostion() - mRightLift->GetDesiredPostion());
	if (error > 2000) {
		mRightLift->GetController()->ResetError();
	}

	mMaxPower = std::max(mRightLift->GetAverageCurrent() * mRightLift->GetAverageVoltage(),mMaxPower);

#ifdef DEBUGGING
	SmartDashboard::PutNumber("ToteCount", mToteCount);
	SmartDashboard::PutNumber("Desired Tote Count", mDesiredToteCount);
	SmartDashboard::PutNumber("stackerRightPosition", mRightLift->GetDesiredPostion());
	SmartDashboard::PutBoolean("stackerRightOnTarget", mRightLift->OnTarget());
	SmartDashboard::PutBoolean("stackerRightResetting", mRightLift->IsResetting());
	SmartDashboard::PutNumber("stackerRightCurrentPosition", mRightLift->GetCurrentPostion());
	SmartDashboard::PutData("stackerRightController", (PIDController*)mRightLift->GetController());
	SmartDashboard::PutNumber("RightStackerState", mRightLift->GetLiftState());
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

void Stacker::UpdateToteCount(){

	if (mMaxPower > TOTE_COUNT_6_CURRENT_THRESHOLD){
		mToteCount = 6;
	}
	else if (mMaxPower > TOTE_COUNT_5_CURRENT_THRESHOLD){
		mToteCount = 5;
	}
	else if (mMaxPower > TOTE_COUNT_4_CURRENT_THRESHOLD){
		mToteCount = 4;
	}
	else if (mMaxPower > TOTE_COUNT_3_CURRENT_THRESHOLD){
		mToteCount = 3;
	}
	else if (mMaxPower > TOTE_COUNT_2_CURRENT_THRESHOLD){
		mToteCount = 2;
	}
	else if (mMaxPower > TOTE_COUNT_1_CURRENT_THRESHOLD){
		mToteCount = 1;
	}
	else {
		mToteCount = 0;
	}
	mMaxPower = 0;
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
