#ifndef CONTROLLERMAP_H
#define CONTROLLERMAP_H

#include "XboxController.h"

//Driver Stick
#define UNLOAD_STACKER_BUTTON       new JoystickButton(driverStick, XboxController::xbBButton)
#define ACQUIRE_TOTE_BUTTON         new AnalogJoystickButton(driverStick, XboxController::xbRightTrigger, .5)
//#define SET_BOOSTING_BUTTON         new JoystickButton(driverStick, XboxController::xbRightBumper)
#define REVERSE_INTAKE_BUTTON		new JoystickButton(driverStick, XboxController::xbRightBumper)
#define SET_ORIGIN_BUTTON           new AnalogJoystickButton(driverStick, XboxController::xbLeftTrigger, .5)
#define TOGGLE_FIELD_CENTRIC_BUTTON new JoystickButton(driverStick, XboxController::xbLeftBumper)

//Note: NEVER PRESS THIS BUTTON!!!!
//#define KILL_EVERYTHING_BUTTON		new JoystickButton(driverStick, XboxController::xbBackButton)

//AUX Stick
#define INTAKE_ON_BUTTON            new JoystickButton(auxStick, XboxController::xbBackButton)
#define STACKER_ON_BUTTON       	new JoystickButton(auxStick, XboxController::xbStartButton)
#define ARM_TWO_TOTE_STACK_BUTTON	new JoystickButton(auxStick, XboxController::xbXButton)
#define ARM_THREE_TOTE_STACK_BUTTON new JoystickButton(auxStick, XboxController::xbYButton)
#define ARM_FOUR_TOTE_STACK_BUTTON  new JoystickButton(auxStick, XboxController::xbBButton)
#define ARM_FIVE_TOTE_STACK_BUTTON  new JoystickButton(auxStick, XboxController::xbAButton)
#define ARM_EXTEND_BUTTON			new POVJoystickButton(auxStick, 0, XboxController::xbDPadTop)
#define ARM_RETRACT_BUTTON			new POVJoystickButton(auxStick, 0, XboxController::xbDPadBottom)
//#define SLIDE_EXTEND_BUTTON		new POVJoystickButton(auxStick, 0, XboxController::xbDPadRight)
//#define SLIDE_RETRACT_BUTTON		new POVJoystickButton(auxStick, 0, XboxController::xbDPadLeft)
#define CO_OP_ON_STEP_BUTTON		new POVJoystickButton(auxStick, 0, XboxController::xbDPadRight)
#define PICK_UP_CO_OP_BUTTON		new POVJoystickButton(auxStick, 0, XboxController::xbDPadLeft)
#define GRIPPER_OPEN_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbLeftXAxis, 0.5f)
#define GRIPPER_CLOSE_BUTTON		new AnalogJoystickButton(auxStick, XboxController::xbLeftXAxis, -0.5f)
//#define ARM_RAISE_BUTTON			new JoystickButton(auxStick, XboxController::xbBackButton)
//#define ARM_LOWER_BUTTON			new JoystickButton(auxStick, XboxController::xbStartButton)
#define ARM_TO_TOP_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbLeftTrigger, .5)
#define ARM_TO_STEP_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbRightTrigger, .5)
#define ARM_TO_BOTTOM_BUTTON		new JoystickButton(auxStick, XboxController::xbRightBumper)
#define ARM_TO_TIPPER_OVER_CAN_BUTTON		new JoystickButton(auxStick, XboxController::xbLeftBumper)
//#define WRIST_TILT_UP_BUTTON		new AnalogJoystickButton(auxStick, XboxController::xbRightYAxis, 0.5f)
//#define WRIST_TILT_DOWN_BUTTON	new AnalogJoystickButton(auxStick, XboxController::xbRightYAxis, -0.5f)
#define WRIST_TO_90_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbRightYAxis, -0.5f)
#define WRIST_TO_180_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbRightXAxis, -0.5f)
#define WRIST_TO_270_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbRightYAxis, 0.5f)

//Debug Stick
#define DRIVETRAIN_INC_I_BUTTON     new JoystickButton(debugStick, XboxController::xbYButton)
#define DRIVETRAIN_INC_P_BUTTON     new JoystickButton(debugStick, XboxController::xbBButton)
#define DRIVETRAIN_DEC_I_BUTTON     new JoystickButton(debugStick, XboxController::xbXButton)
#define DRIVETRAIN_DEC_P_BUTTON     new JoystickButton(debugStick, XboxController::xbAButton)

#endif
