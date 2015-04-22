#ifndef CONTROLLERMAP_H
#define CONTROLLERMAP_H

#include "XboxController.h"

//Driver Stick
#define UNLOAD_STACKER_BUTTON       new JoystickButton(driverStick, XboxController::xbBButton)
#define DRIVE_ON_TO_PLATFORM_BUTTON new JoystickButton(driverStick, XboxController::xbXButton)
#define ACQUIRE_TOTE_BUTTON         new AnalogJoystickButton(driverStick, XboxController::xbRightTrigger, .5)
//#define SET_BOOSTING_BUTTON         new JoystickButton(driverStick, XboxController::xbRightBumper)
#define REVERSE_INTAKE_BUTTON		new JoystickButton(driverStick, XboxController::xbRightBumper)
#define SET_ORIGIN_BUTTON           new AnalogJoystickButton(driverStick, XboxController::xbLeftTrigger, .5)
#define TOGGLE_FIELD_CENTRIC_BUTTON new JoystickButton(driverStick, XboxController::xbLeftBumper)
#define LENGTHEN_POLES_BUTTON		new JoystickButton(driverStick, XboxController::xbXButton)

//Note: NEVER PRESS THIS BUTTON!!!!
//#define KILL_EVERYTHING_BUTTON		new JoystickButton(driverStick, XboxController::xbBackButton)

//AUX Stick
//#define ORIGINAL_CONTROLS
#ifndef ORIGINAL_CONTROLS
//#define INTAKE_ON_BUTTON            new JoystickButton(auxStick, XboxController::xbBackButton)
#define STACKER_ON_BUTTON       	new JoystickButton(auxStick, 1)

#define ARM_TWO_TOTE_STACK_BUTTON	new JoystickButton(auxStick, XboxController::xbXButton)
#define ARM_THREE_TOTE_STACK_BUTTON new JoystickButton(auxStick, XboxController::xbYButton)
#define ARM_FOUR_TOTE_STACK_BUTTON  new JoystickButton(auxStick, 3)
#define DROP_CAN_ON_TOTES_BUTTON	new JoystickButton(auxStick, 2)

#define SIX_TOTES_BUTTON			new JoystickButton(auxStick, 6)
#define FIVE_TOTES_BUTTON			new JoystickButton(auxStick, 7)
#define FOUR_TOTES_BUTTON			new JoystickButton(auxStick, 8)
#define THREE_TOTES_BUTTON			new JoystickButton(auxStick, 9)
#define TWO_TOTES_BUTTON			new JoystickButton(auxStick, 10)
#define ONE_TOTE_BUTTON				new JoystickButton(auxStick, 11)

#define ARM_TO_45					new JoystickButton(auxStick, 4)


//#define SLIDE_EXTEND_BUTTON		new POVJoystickButton(auxStick, 0, XboxController::xbDPadRight)
//#define SLIDE_RETRACT_BUTTON		new POVJoystickButton(auxStick, 0, XboxController::xbDPadLeft)
#define CO_OP_ON_STEP_BUTTON		new AnalogJoystickButton(auxStick, 0, .5);
#define PICK_UP_CO_OP_BUTTON		new AnalogJoystickButton(auxStick, 0, -.5);
//#define GRIPPER_OPEN_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbLeftXAxis, 0.5f)
//#define GRIPPER_CLOSE_BUTTON		new AnalogJoystickButton(auxStick, XboxController::xbLeftXAxis, -0.5f)
//#define ARM_RAISE_BUTTON			new JoystickButton(auxStick, XboxController::xbBackButton)
//#define ARM_LOWER_BUTTON			new JoystickButton(auxStick, XboxController::xbStartButton)
#define GRIPPER_OPEN_BUTTON			new JoystickButton(auxRStick, 1);
#define ARM_EXTEND_BUTTON			new AnalogJoystickButton(auxRStick, 1, -.5);
#define ARM_RETRACT_BUTTON			new AnalogJoystickButton(auxRStick, 1, .5);
#define ARM_TO_TOP_BUTTON			new JoystickButton(auxRStick, 4);
#define ARM_TO_STEP_BUTTON			new JoystickButton(auxRStick, 3);
#define ARM_TO_BOTTOM_BUTTON		new JoystickButton(auxRStick, 5);
#define ARM_TO_TIPPER_OVER_CAN_BUTTON		new JoystickButton(auxRStick, 2);
#define ARM_TO_PRE_TIPPER_OVER_CAN_BUTTON	new JoystickButton(auxStick, 5);
#define ARM_RAISE_BUTTON			new JoystickButton(auxRStick, 7)
#define ARM_LOWER_BUTTON			new JoystickButton(auxRStick, 6)
//#define WRIST_TILT_UP_BUTTON		new AnalogJoystickButton(auxStick, XboxController::xbRightYAxis, 0.5f)
//#define WRIST_TILT_DOWN_BUTTON	new AnalogJoystickButton(auxStick, XboxController::xbRightYAxis, -0.5f)
#define WRIST_TO_90_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbRightYAxis, -0.5f)
#define WRIST_TO_180_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbRightXAxis, -0.5f)
#define WRIST_TO_270_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbRightYAxis, 0.5f)
#else
#define INTAKE_ON_BUTTON            new JoystickButton(auxStick, XboxController::xbBackButton)
#define STACKER_ON_BUTTON       	new JoystickButton(auxStick, XboxController::xbStartButton)
#define ARM_TWO_TOTE_STACK_BUTTON	new JoystickButton(auxStick, XboxController::xbXButton)
#define ARM_THREE_TOTE_STACK_BUTTON new JoystickButton(auxStick, XboxController::xbYButton)
#define ARM_FOUR_TOTE_STACK_BUTTON  new JoystickButton(auxStick, XboxController::xbBButton)
#define GRIPPER_OPEN_BUTTON			new JoystickButton(auxStick, XboxController::xbAButton)
#define ARM_EXTEND_BUTTON			new POVJoystickButton(auxStick, 0, XboxController::xbDPadTop)
#define ARM_RETRACT_BUTTON			new POVJoystickButton(auxStick, 0, XboxController::xbDPadBottom)
//#define SLIDE_EXTEND_BUTTON		new POVJoystickButton(auxStick, 0, XboxController::xbDPadRight)
//#define SLIDE_RETRACT_BUTTON		new POVJoystickButton(auxStick, 0, XboxController::xbDPadLeft)
#define CO_OP_ON_STEP_BUTTON		new POVJoystickButton(auxStick, 0, XboxController::xbDPadRight)
#define PICK_UP_CO_OP_BUTTON		new POVJoystickButton(auxStick, 0, XboxController::xbDPadLeft)
//#define GRIPPER_OPEN_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbLeftXAxis, 0.5f)
//#define GRIPPER_CLOSE_BUTTON		new AnalogJoystickButton(auxStick, XboxController::xbLeftXAxis, -0.5f)
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
#endif

//Debug Stick
#define DRIVETRAIN_INC_I_BUTTON     new JoystickButton(debugStick, XboxController::xbYButton)
#define DRIVETRAIN_INC_P_BUTTON     new JoystickButton(debugStick, XboxController::xbBButton)
#define DRIVETRAIN_DEC_I_BUTTON     new JoystickButton(debugStick, XboxController::xbXButton)
#define DRIVETRAIN_DEC_P_BUTTON     new JoystickButton(debugStick, XboxController::xbAButton)


#endif
