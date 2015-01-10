#ifndef Stacker_H
#define Stacker_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Components/Lift2481.h"


class Stacker: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Lift2481* mRightLift;
	Lift2481* mLeftLift;
public:
	Stacker();
	void InitDefaultCommand();
	void Reset();
	bool OnTarget();
	void SetPosition(float);
	void PeriodicUpdate();
	void Stop();
	bool IsResetting();
};

#endif
