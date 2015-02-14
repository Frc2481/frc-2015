#ifndef Slide_H
#define Slide_H

#include "Commands/Subsystem.h"
#include "WPILib.h"

class Slide: public Subsystem
{
private:
	Solenoid* mExtender;
public:
	Slide();
	void InitDefaultCommand();
	void Extend();
	void Retract();
	bool Get();
};

#endif
