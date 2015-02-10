#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "ControllerMap.h"
#include "Components/Joystick2481.h"
#include "Components/AnalogJoystickButton.h"


class OI
{
private:
	static const int DRIVER_STICK_PORT = 1;
	static const int AUX_STICK_PORT = 2;
	static const int DEBUG_STICK_PORT = 3;
	Joystick2481* driverStick;
	Joystick* auxStick;
	Joystick* debugStick;

	//Driver Stick
	Button* acquireTote;
	Button* setBoosting;
	Button* setOrigin;
	Button* unloadStacker;
	Button* toggleFieldCentric;
	bool boosting;

	//debug stick
	Button* incP;
	Button* decP;
	Button* incI;
	Button* decI;

	//aux stick
	Button* intakeOn;
	Button* intakeReverse;
	Button* toggleArm;
	Button* stackerOn;
	Button* stackerPickup;
	Button* scoringPlatformHeight;
	Button* armExtend;
	Button* armRetract;
	Button* gripperOpen;
	Button* gripperClose;
	AnalogJoystickButton* armRaise;
	AnalogJoystickButton* armLower;
	AnalogJoystickButton* armTop;
	AnalogJoystickButton* armBottom;


public:
	OI();
	Joystick2481* GetDriverStick();
	Joystick* GetAuxStick();
	Joystick* GetDebugStick();

	void SetBoosting(bool boost);
	bool GetBoosting();
};

#endif
