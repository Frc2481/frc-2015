#ifndef COMMAND_BASE_H
#define COMMAND_BASE_H

#include <string>
#include "Commands/Command.h"
#include "Subsystems/Stacker.h"
#include "Subsystems/DriveTrain.h"
#include "Subsystems/Intake.h"
#include "Subsystems/Arm.h"
#include "Subsystems/Slide.h"
#include "Subsystems/FishingPoles.h"
#include "OI.h"
#include "WPILib.h"

/**
 * The base for all commands. All atomic commands should subclass CommandBase.
 * CommandBase stores creates and stores each control system. To access a
 * subsystem elsewhere in your code in your code use CommandBase.examplesubsystem
 */
class CommandBase: public Command
{
public:
	CommandBase(char const *name);
	CommandBase();
	static void init();

	// Create a single static instance of all of your subsystems
	static DriveTrain* driveTrain;
	static Intake* intake;
	static Stacker *stacker;
	static Arm* arm;
	static Slide* slide;
	static FishingPoles* fishingPoles;

	static OI *oi;
};

#endif
