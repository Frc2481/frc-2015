#ifndef CONTROLLERMAP_H
#define CONTROLLERMAP_H

#include "XboxController.h"

#define INTAKE_ON_BUTTON           new JoystickButton(auxStick, XboxController::xbLeftBumper)
#define INTAKE_REVERSE_BUTTON      new JoystickButton(auxStick, XboxController::xbBButton)
#define PIVOT_TOGGLE_BUTTON        new JoystickButton(auxStick, XboxController::xbYButton)

#endif
