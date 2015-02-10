#ifndef CONTROLLERMAP_H
#define CONTROLLERMAP_H

#include "XboxController.h"

//Driver Stick
#define UNLOAD_STACKER_BUTTON       new JoystickButton(driverStick, XboxController::xbXButton)
#define ACQUIRE_TOTE_BUTTON         new JoystickButton(driverStick, XboxController::xbAButton)
#define SET_BOOSTING_BUTTON         new JoystickButton(driverStick, XboxController::xbLeftStickClick)
#define SET_ORIGIN_BUTTON           new JoystickButton(driverStick, XboxController::xbLeftBumper)
#define TOGGLE_FIELD_CENTRIC_BUTTON new JoystickButton(driverStick, XboxController::xbRightTrigger)

//AUX Stick
#define INTAKE_ON_BUTTON            new JoystickButton(auxStick, XboxController::xbLeftBumper)
#define INTAKE_REVERSE_BUTTON       new JoystickButton(auxStick, XboxController::xbRightBumper)
#define PIVOT_TOGGLE_BUTTON         new JoystickButton(auxStick, XboxController::xbYButton)
#define STACKER_ON_BUTTON           new JoystickButton(auxStick, XboxController::xbXButton)
#define STACKER_PICKUP_TOTE_BUTTON  new JoystickButton(auxStick, XboxController::xbBButton)
#define STACKER_TO_PLATFORM_BUTTON  new JoystickButton(auxStick, XboxController::xbAButton)
#define ARM_EXTEND_BUTTON			new JoystickButton(auxStick, XboxController::xbDPadTop)
#define ARM_RETRACT_BUTTON			new JoystickButton(auxStick, XboxController::xbDPadBottom)
#define GRIPPER_OPEN_BUTTON			new JoystickButton(auxStick, XboxController::xbDPadRight)
#define GRIPPER_CLOSE_BUTTON		new JoystickButton(auxStick, XboxController::xbDPadLeft)
#define ARM_RAISE_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbRightYAxis, 0.5f)
#define ARM_LOWER_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbRightYAxis, -0.5f)
#define ARM_TO_TOP_BUTTON			new AnalogJoystickButton(auxStick, XboxController::xbLeftYAxis, 0.5f)
#define ARM_TO_BOTTOM_BUTTON		new AnalogJoystickButton(auxStick, XboxController::xbLeftYAxis, -0.5f)

//Debug Stick
#define DRIVETRAIN_INC_I_BUTTON     new JoystickButton(debugStick, XboxController::xbYButton)
#define DRIVETRAIN_INC_P_BUTTON     new JoystickButton(debugStick, XboxController::xbBButton)
#define DRIVETRAIN_DEC_I_BUTTON     new JoystickButton(debugStick, XboxController::xbXButton)
#define DRIVETRAIN_DEC_P_BUTTON     new JoystickButton(debugStick, XboxController::xbAButton)

#endif
