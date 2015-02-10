//#include <Commands/CalibrateEncoderOffsetsCommand.h>
#include <Commands/PickUpToteCommand.h>
#include "OI.h"
#include "Commands/IntakeCCW.h"
#include "Commands/IntakeCW.h"
#include "Commands/IntakeTurnOff.h"
#include "Commands/IntakeTurnOn.h"
#include "Commands/IntakeTurnOnReverse.h"
#include "Commands/StackerGoToBottomCommand.h"
#include "Commands/StackerGoToScoringPlatformCommand.h"
#include "Commands/StackerGoToStepCommand.h"
#include "Commands/StackerGoToTopCommand.h"
#include "Commands/StackerResetCommand.h"
//#include "Commands/DriveCommand.h"
#include "Commands/IntakeManualCommand.h"
#include "Commands/StackerSetSpeed.h"
#include "Commands/StackerManualCommand.h"
#include "Commands/StackerTurnOff.h"
#include "Commands/AcquireToteCommand.h"
#include "Commands/OISetBoosting.h"
#include "Commands/SetOriginCommand.h"
#include "Commands/UnloadStackerManual.h"
#include "Commands/UnloadToteStackManualCommandGroup.h"
#include "Commands/ToggleFieldCentricCommand.h"
#include "Commands/ArmRaiseCommand.h"
#include "Commands/ArmLowerCommand.h"
#include "Commands/ArmGripperOpenCommand.h"
#include "Commands/ArmGripperCloseCommand.h"
#include "Commands/ArmGotoPositionCommand.h"
#include "Commands/ArmExtendCommand.h"
#include "Commands/ArmRetractCommand.h"


#include "Commands/SetICommand.h"
#include "Commands/SetPCommand.h"
#include "Components/Joystick2481.h"


OI::OI()
{
	// Process operator interface input here.
	driverStick = new Joystick2481(DRIVER_STICK_PORT);
	auxStick = new Joystick(AUX_STICK_PORT);
	debugStick = new Joystick(DEBUG_STICK_PORT);

	//toggle field centric
	toggleFieldCentric = TOGGLE_FIELD_CENTRIC_BUTTON;
	toggleFieldCentric->WhileHeld(new ToggleFieldCentricCommand());

	//Set Origin
	setOrigin = SET_ORIGIN_BUTTON;
	setOrigin->WhileHeld(new SetOriginCommand(0, (ROBOT_LENGTH / 2) + 10));

	//OI Set Boosting
	setBoosting = SET_BOOSTING_BUTTON;
	setBoosting->WhileHeld(new OISetBoosting());

	//Unload Stacker
	unloadStacker = UNLOAD_STACKER_BUTTON;
	unloadStacker->WhileHeld(new UnloadToteStackCommandGroup());

	//acquire tote
	acquireTote = ACQUIRE_TOTE_BUTTON;
	acquireTote->WhenPressed(new AcquireToteCommand());

    //intakeOn
	intakeOn = INTAKE_ON_BUTTON;
	intakeOn->WhileHeld(new IntakeManualCommand());

	//intakeReverse
	intakeReverse = INTAKE_REVERSE_BUTTON;
	intakeReverse->WhileHeld(new IntakeTurnOnReverse());

	//Arm Raise
	armRaise = ARM_RAISE_BUTTON;
	armRaise->WhileHeld(new ArmRaiseCommand());

	//Arm Lower
	armLower = ARM_LOWER_BUTTON;
	armLower->WhileHeld(new ArmLowerCommand());

	//Arm Extend
	armExtend = ARM_EXTEND_BUTTON;
	armExtend->WhenPressed(new ArmExtendCommand());

	//Arm Retract
	armRetract = ARM_RETRACT_BUTTON;
	armRetract->WhenPressed(new ArmRetractCommand());

	//Arm Gripper Open
	gripperOpen = GRIPPER_OPEN_BUTTON;
	gripperOpen->WhenPressed(new ArmGripperOpenCommand());

	//Arm Gripper Close
	gripperClose = GRIPPER_CLOSE_BUTTON;
	gripperClose->WhenPressed(new ArmGripperCloseCommand());

	//Arm Go To Set Position
	armTop = ARM_TO_TOP_BUTTON;
	armTop->WhenPressed(new ArmGoToPositionCommand(ARM_PIVOT_POSITION_TOP));

	armBottom = ARM_TO_BOTTOM_BUTTON;
	armBottom->WhenPressed(new ArmGoToPositionCommand(ARM_PIVOT_POSITION_BOT));

    //Set Stacker
	stackerOn = STACKER_ON_BUTTON;
	stackerOn->WhileHeld(new StackerManualCommand());

	stackerPickup = STACKER_PICKUP_TOTE_BUTTON;
	stackerPickup->WhenPressed(new PickUpToteCommand());

	scoringPlatformHeight = STACKER_TO_PLATFORM_BUTTON;
	scoringPlatformHeight->WhenPressed(new StackerGoToScoringPlatformCommand());

	//Drivetrain Set P
	incP = DRIVETRAIN_INC_P_BUTTON;
	incP->WhenPressed(new SetPCommand(true));

	decP = DRIVETRAIN_DEC_P_BUTTON;
	decP->WhenPressed(new SetPCommand(false));

	//Drivetrain Set I
	incI = DRIVETRAIN_INC_I_BUTTON;
	incI->WhenPressed(new SetICommand(true));

	decI = DRIVETRAIN_DEC_I_BUTTON;
	decI->WhenPressed(new SetICommand(false));

}

void OI::SetBoosting(bool boost){
	boosting = boost;
}

bool OI::GetBoosting(){
	return boosting;
}

Joystick2481* OI::GetDriverStick(){
	return driverStick;
}

Joystick* OI::GetAuxStick(){
	return auxStick;
}

Joystick* OI::GetDebugStick(){
	return debugStick;
}
