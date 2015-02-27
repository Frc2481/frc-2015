#include "CommandBase.h"
#include "Subsystems/Stacker.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
DriveTrain* CommandBase::driveTrain = NULL;
Intake* CommandBase::intake = NULL;
Stacker* CommandBase::stacker = NULL;
Arm* CommandBase::arm = NULL;
Slide* CommandBase::slide = NULL;
FishingPoles* CommandBase::fishingPoles = NULL;

OI* CommandBase::oi = NULL;

CommandBase::CommandBase(char const *name) :
		Command(name)
{
}

CommandBase::CommandBase() :
		Command()
{

}

void CommandBase::init()
{
	// Create a single static instance of all of your subsystems. The following
	// line should be repeated for each subsystem in the project.

	driveTrain = new DriveTrain();
	intake = new Intake();
	stacker = new Stacker();
	arm = new Arm();
	slide = new Slide();
	fishingPoles = new FishingPoles();

	oi = new OI();

	driveTrain->SetLengthAndWidth(ROBOT_LENGTH, ROBOT_WIDTH);
}
