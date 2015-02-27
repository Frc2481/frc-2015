#include "FishingPoles.h"
#include "../RobotMap.h"
#include "RobotParameters.h"

FishingPoles::FishingPoles() :
		Subsystem("FishingPoles")
{
	mFishingPole = new Solenoid(FISHING_POLE_SOLENOID);
}

void FishingPoles::InitDefaultCommand(){
}

void FishingPoles::Cast() {
	mFishingPole->Set(true);
}

void FishingPoles::Reel() {
	mFishingPole->Set(false);
}

bool FishingPoles::GoneFishing() {
	return mFishingPole->Get();
}
