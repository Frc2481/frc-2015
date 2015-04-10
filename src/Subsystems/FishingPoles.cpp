#include "FishingPoles.h"
#include "../RobotMap.h"
#include "RobotParameters.h"

FishingPoles::FishingPoles() :
		Subsystem("FishingPoles")
{
	mFishingPoleL = new Solenoid(FISHING_POLE_SOLENOID_L);
	mFishingPoleR = new Solenoid(FISHING_POLE_SOLENOID_R);
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
