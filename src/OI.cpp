#include "OI.h"
#include "Commands/IntakeCCW.h"
#include "Commands/IntakeCW.h"
#include "Commands/IntakeTurnOff.h"
#include "Commands/IntakeTurnOn.h"
#include "Commands/IntakeTurnOnReverse.h"
#include "Commands/ApplyEncoderOffsetsCommand.h"
#include "Commands/PickUpTote.h"
#include "Commands/StackerGoToBottomCommand.h"
#include "Commands/StackerGoToScoringPlatformCommand.h"
#include "Commands/StackerGoToStepCommand.h"
#include "Commands/StackerGoToTopCommand.h"
#include "Commands/StackerResetCommand.h"
#include "Commands/DriveCommand.h"
#include "Commands/IntakeManualCommand.h"
#include "Commands/ArmToggleLockCommand.h"


OI::OI()
{
	// Process operator interface input here.
	driverStick = new Joystick(DRIVER_STICK_PORT);
	auxStick = new Joystick(AUX_STICK_PORT);

    //intakeOn
	intakeOn = INTAKE_ON_BUTTON;
	intakeOn->WhileHeld(new IntakeManualCommand());
	intakeOn->WhenReleased(new IntakeTurnOff());

	//intakeReverse
	intakeReverse = INTAKE_REVERSE_BUTTON;
	intakeReverse->WhileHeld(new IntakeTurnOnReverse);
	intakeReverse->WhenReleased(new IntakeTurnOff);

	//Toggle Arm
	toggleArm = PIVOT_TOGGLE_BUTTON;
	toggleArm->WhenPressed(new ArmToggleLockCommand);
}

Joystick* OI::GetDriverStick(){
	return driverStick;
}

Joystick* OI::GetAuxStick(){
	return auxStick;
}
