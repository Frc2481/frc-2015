#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "ControllerMap.h"


class OI
{
private:
	static const int DRIVER_STICK_PORT = 1;
	static const int AUX_STICK_PORT = 2;
	Joystick* driverStick;
	Joystick* auxStick;
	Button* intakeOn;
	Button* intakeReverse;
	Button* toggleArm;
public:
	OI();
	Joystick* GetDriverStick();
	Joystick* GetAuxStick();
};

#endif
