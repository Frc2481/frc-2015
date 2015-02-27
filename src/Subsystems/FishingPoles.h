#ifndef FishingPoles_H
#define FishingPoles_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class FishingPoles: public Subsystem
{
private:
	Solenoid* mFishingPole;

public:
	FishingPoles();
	void InitDefaultCommand();
	void Cast();
	void Reel();
	bool GoneFishing();
};

#endif
