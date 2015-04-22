#include "FishingPoles.h"
#include "../RobotMap.h"
#include "RobotParameters.h"

FishingPoles::FishingPoles() :
		Subsystem("FishingPoles")
{
	mFishingPoleL = new Solenoid(FISHING_POLE_SOLENOID_L);
	mFishingPoleR = new Solenoid(FISHING_POLE_SOLENOID_R);
	mFishingPoleLength = new Solenoid(FISHING_POLE_SOLENOID_LENGTH);
}

void FishingPoles::InitDefaultCommand(){
}

void FishingPoles::Cast() {
	mFishingPoleL->Set(true);
	mFishingPoleR->Set(true);
}

void FishingPoles::Reel() {
	mFishingPoleL->Set(false);
	mFishingPoleR->Set(false);
}

bool FishingPoles::GoneFishing() {
	return mFishingPoleL->Get();
}

void FishingPoles::Shorten() {
	mFishingPoleLength->Set(true);
}

void FishingPoles::Lengthen() {
	mFishingPoleLength->Set(false);
}

bool FishingPoles::GetLength() {
	return mFishingPoleLength->Get();
}
