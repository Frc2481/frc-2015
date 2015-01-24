#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "Commands/StackerResetCommand.h"
#include "Commands/PickUpTote.h"
#include "Commands/IncrementToteCountCommand.h"
#include "Commands/DecrementToteCountCommand.h"
#include "Commands/StackerSetFeedbackCommand.h"

class Robot: public IterativeRobot
{
private:
	Command *autonomousCommand;
	LiveWindow *lw;

	void RobotInit()
	{
		CommandBase::init();
		autonomousCommand = new ExampleCommand();
		lw = LiveWindow::GetInstance();

		SmartDashboard::PutData("Increment Tote Count", new IncrementToteCountCommand());
		SmartDashboard::PutData("Decrement Tote Count", new DecrementToteCountCommand());
		SmartDashboard::PutData("Reset Stacker", new StackerResetCommand());
		SmartDashboard::PutData("Pickup Tote", new PickUpTote());
		SmartDashboard::PutData("Disable Right Lift", new StackerSetFeedbackCommand(Stacker::RIGHT, false));
		SmartDashboard::PutData("Enable Right Lift", new StackerSetFeedbackCommand(Stacker::RIGHT, true));
		SmartDashboard::PutData("Disable Left Lift", new StackerSetFeedbackCommand(Stacker::LEFT,false));
		SmartDashboard::PutData("Enable Left Lift", new StackerSetFeedbackCommand(Stacker::LEFT,true));
	}
	
	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
	}

	void AutonomousInit()
	{
		if (autonomousCommand != NULL)
			autonomousCommand->Start();
	}

	void AutonomousPeriodic()
	{
		Scheduler::GetInstance()->Run();
		CommandBase::stacker->PeriodicUpdate();
	}

	void TeleopInit()
	{
		// This makes sure that the autonomous stops running when
		// teleop starts running. If you want the autonomous to 
		// continue until interrupted by another command, remove
		// this line or comment it out.
		if (autonomousCommand != NULL)
			autonomousCommand->Cancel();
	}

	void TeleopPeriodic()
	{
		Scheduler::GetInstance()->Run();
		CommandBase::stacker->PeriodicUpdate();
	}

	void TestPeriodic()
	{
		lw->Run();
	}
};

START_ROBOT_CLASS(Robot);

