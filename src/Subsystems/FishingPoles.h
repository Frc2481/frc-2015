#ifndef FishingPoles_H
#define FishingPoles_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class FishingPoles: public Subsystem
{
private:
	Solenoid* mFishingPoleL;
	Solenoid* mFishingPoleR;
	Solenoid* mFishingPoleLength;

public:
	FishingPoles();
	void InitDefaultCommand();
	void Cast();
	void Reel();
	void Shorten();
	void Lengthen();
	bool GoneFishing();
	bool GetLength();
};

#endif
