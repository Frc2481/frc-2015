#include "CommandBase.h"
#include "Subsystems/Stacker.h"
#include "Commands/Scheduler.h"

// Initialize a single static instance of all of your subsystems to NULL
Stacker* CommandBase::stacker = NULL;
DriveTrain* CommandBase::driveTrain = NULL;
Intake* CommandBase::intake = NULL;
OI* CommandBase::oi = NULL;
Arm* CommandBase::arm = NULL;

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
	intake = new Intake(11,12,4);
	stacker = new Stacker();
	arm = new Arm(0,1,13,14,15,0);

	oi = new OI();

	driveTrain->SetLengthAndWidth(ROBOT_LENGTH, ROBOT_WIDTH);
}
