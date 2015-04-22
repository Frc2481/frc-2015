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
	static const int AUX_RIGHT_STICK_PORT = 3;
	static const int DEBUG_STICK_PORT = 4;
	Joystick2481* driverStick;
	Joystick* auxStick;
	Joystick* auxRStick;
	Joystick* debugStick;

	//Driver Stick
	Button* acquireTote;
	Button* reverseIntake;
	Button* setBoosting;
	Button* setOrigin;
	Button* unloadStacker;
	Button* driveOnToScoringPlatform;
	Button* toggleFieldCentric;
	Button* stackerStep;
	Button* lengthenPoles;
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
//	Button* slideExtend;
//	Button* slideRetract;
	Button* coOpOnStep;
	Button* pickCoOpUp;
	Button* armExtend;
	Button* armRetract;
	Button* gripperOpen;
	Button* armRaise;
	Button* armLower;
	Button* armTop;
	Button* armBottom;
	Button* armToStep;
	Button* armToTippedOverCan;
	Button* armToPreTippedOverCan;
	Button* wristTo90;
	Button* wristTo180;
	Button* wristTo270;
	Button* armTo2Tote;
	Button* armTo3Tote;
	Button* armTo4Tote;
	Button* armTo5Tote;
	Button* armDropOnTotes;
	Button* gripperShudder;

	Button* sixStack;
	Button* fiveStack;
	Button* fourStack;
	Button* threeStack;
	Button* twoStack;
	Button* oneStack;

	Button* actualSixTotes;
	Button* actualFiveTotes;
	Button* actualFourTotes;
	Button* actualThreeTotes;
	Button* actualTwoTotes;
	Button* actualOneTote;

	Button* armTo45;


public:
	OI();
	Joystick2481* GetDriverStick();
	Joystick* GetAuxStick();
	Joystick* GetAuxRightStick();
	Joystick* GetDebugStick();

	void SetBoosting(bool boost);
	bool GetBoosting();
};

#endif
