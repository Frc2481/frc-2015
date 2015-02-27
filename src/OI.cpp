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
#include "Commands/ArmShoulderToSetPoint.h"
#include "Commands/ArmExtendCommand.h"
#include "Commands/ArmRetractCommand.h"
#include "Commands/WristTiltUpCommand.h"
#include "Commands/WristTiltDownCommand.h"
#include "Commands/ExtendSlideCommand.h"
#include "Commands/RetractSlideCommand.h"
#include "Commands/ArmWristToSetPoint.h"
#include "Commands/ArmShoulderToSetPoint.h"
#include "Commands/KILL_EVERYTHING_COMMAND.h"
#include "Commands/UnloadCoOpOnStepCommandGroup.h"
#include "Commands/PickUpCoOpStackCommandGroup.h"


#include "Commands/SetICommand.h"
#include "Commands/SetPCommand.h"
#include "Components/Joystick2481.h"


OI::OI()
{
	// Process operator interface input here.
	driverStick = new Joystick2481(DRIVER_STICK_PORT);
	auxStick = new Joystick(AUX_STICK_PORT);
	debugStick = new Joystick(DEBUG_STICK_PORT);

	//Driver Stick

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

	//acquire tote		Joystick Button 1
	acquireTote = ACQUIRE_TOTE_BUTTON;
	acquireTote->WhenPressed(new AcquireToteCommand());

	//Reverse Intake
	reverseIntake = REVERSE_INTAKE_BUTTON;
	reverseIntake->WhileHeld(new IntakeTurnOnReverse());

	//Kill All Button
	killAll = KILL_EVERYTHING_BUTTON;
	killAll->WhenPressed(new KILL_EVERYTHING_COMMAND());

	//Aux Stick

    //intakeOn
	intakeOn = INTAKE_ON_BUTTON;
	intakeOn->WhileHeld(new IntakeManualCommand());

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
	armTop->WhenPressed(new ArmShoulderToSetPoint(ARM_PIVOT_POSITION_TOP));

	armBottom = ARM_TO_BOTTOM_BUTTON;
	armBottom->WhenPressed(new ArmShoulderToSetPoint(ARM_PIVOT_POSITION_BOT));

	armToStep = ARM_TO_STEP_BUTTON;
	armToStep->WhenPressed(new ArmShoulderToSetPoint(80));

	armTo2Tote = ARM_TWO_TOTE_STACK_BUTTON;
	armTo2Tote->WhenPressed(new ArmShoulderToSetPoint(63));

	armTo3Tote = ARM_THREE_TOTE_STACK_BUTTON;
	armTo3Tote->WhenPressed(new ArmShoulderToSetPoint(50));

	armTo4Tote = ARM_FOUR_TOTE_STACK_BUTTON;
	armTo4Tote->WhenPressed(new ArmShoulderToSetPoint(32));

	armTo5Tote = ARM_FIVE_TOTE_STACK_BUTTON;
	armTo5Tote->WhenPressed(new ArmShoulderToSetPoint(14));

	//Co Op Totes
	coOpOnStep = CO_OP_ON_STEP_BUTTON;
	coOpOnStep->WhenPressed(new UnloadCoOpOnStepCommandGroup());

	pickCoOpUp = PICK_UP_CO_OP_BUTTON;
	pickCoOpUp->WhenPressed(new PickUpCoOpStackCommandGroup());

	//Wrist To Setpoint
	wristTo90 = WRIST_TO_90_BUTTON;
	wristTo90->WhenPressed(new ArmWristToSetPoint(90));

	wristTo180 = WRIST_TO_180_BUTTON;
	wristTo180->WhenPressed(new ArmWristToSetPoint(180));

	wristTo270 = WRIST_TO_270_BUTTON;
	wristTo270->WhenPressed(new ArmWristToSetPoint(270));

    //Stacker Manual
	stackerOn = STACKER_ON_BUTTON;
	stackerOn->WhileHeld(new StackerManualCommand());

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

	boosting = false;

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
