#ifndef OI_H
#define OI_H

#include "WPILib.h"
#include "ControllerMap.h"
#include "Components/Joystick2481.h"
#include "Components/AnalogJoystickButton.h"
#include "Components/POVJoystickButton.h"


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
	Button* reverseIntake;
	Button* setBoosting;
	Button* setOrigin;
	Button* unloadStacker;
	Button* toggleFieldCentric;
	Button* stackerStep;
	bool boosting;

	Button* killAll;

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
//	Button* slideExtend;
//	Button* slideRetract;
	Button* coOpOnStep;
	Button* pickCoOpUp;
	Button* armExtend;
	Button* armRetract;
	Button* gripperOpen;
	Button* gripperClose;
//	Button* armRaise;
//	Button* armLower;
	Button* armTop;
	Button* armBottom;
	Button* armToStep;
	Button* armToTippedOverCan;
	Button* wristTo90;
	Button* wristTo180;
	Button* wristTo270;
	Button* armTo2Tote;
	Button* armTo3Tote;
	Button* armTo4Tote;
	Button* armTo5Tote;


public:
	OI();
	Joystick2481* GetDriverStick();
	Joystick* GetAuxStick();
	Joystick* GetDebugStick();

	void SetBoosting(bool boost);
	bool GetBoosting();
};

#endif
