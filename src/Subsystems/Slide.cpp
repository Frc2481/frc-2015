#include "Slide.h"
#include "../RobotParameters.h"

Slide::Slide() :
		Subsystem("Slide"){
		mExtender = new Solenoid(EXTENDER_SOLENOID);
}

void Slide::InitDefaultCommand(){}

void Slide::Extend() {
	mExtender->Set(true);
}

void Slide::Retract() {
	mExtender->Set(false);
}

bool Slide::Get() {
	return mExtender->Get();
}
