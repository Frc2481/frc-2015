//#include <Commands/CalibrateEncoderOffsetsCommand.h>
#include <Commands/PickUpToteCommand.h>
#include "WPILib.h"
#include "Commands/Command.h"
#include "Commands/ExampleCommand.h"
#include "CommandBase.h"
#include "Commands/StackerResetCommand.h"
#include "Commands/IntakeTurnOn.h"
#include "Commands/IntakeTurnOff.h"
#include "Commands/IntakeTurnOnReverse.h"
#include "Commands/IntakeCW.h"
#include "Commands/IntakeCCW.h"
#include "Commands/ArmGoToPositionCommand.h"
#include "Commands/IncrementToteCountCommand.h"
#include "Commands/DecrementToteCountCommand.h"
#include "Commands/StackerSetFeedbackCommand.h"
#include "Commands/StackerZeroEncodersCommand.h"
#include "Commands/StackerGoToTopCommand.h"
#include "Commands/CalibrateEncoderOffsetsCommand.h"
#include "Commands/SaveCommand.h"
#include "Commands/StackerDisableBrakeCommand.h"
#include "Commands/AcquireToteCommand.h"
#include "Commands/StackerGoToScoringPlatformCommand.h"
#include "Commands/PickUpToteToScoringPlatformCommand.h"
#include "Commands/CalibrateArmEncoderOffsetsCommand.h"


#include "RobotParameters.h"

using namespace std;
class Robot: public IterativeRobot
{
private:
	Command *autonomousCommand;
	LiveWindow *lw;

	void RobotInit()
	{
		CommandBase::init();
		//autonomousCommand = new ThreeToteStackAutoCommand();
		lw = LiveWindow::GetInstance();

		SmartDashboard::PutData(Scheduler::GetInstance());
		SmartDashboard::PutData("SAVE", new SaveCommand());
		SmartDashboard::PutData("Increment Tote Count", new IncrementToteCountCommand());
		SmartDashboard::PutData("Decrement Tote Count", new DecrementToteCountCommand());
		SmartDashboard::PutData("Reset Stacker", new StackerResetCommand());
		SmartDashboard::PutData("disable Brake", new StackerDisableBrakeCommand());
		SmartDashboard::PutData("Pickup Tote", new PickUpToteCommand());
		SmartDashboard::PutData("Pickup Tote To Scoring Platform", new PickUpToteToScoringPlatformCommand());
		SmartDashboard::PutData("Calibrate Encoder Offsets", new CalibrateEncoderOffsetsCommand());
		SmartDashboard::PutData("Turn Intake On", new IntakeTurnOn());
		SmartDashboard::PutData("Turn Intake Off", new IntakeTurnOff());
		SmartDashboard::PutData("Reverse Intake", new IntakeTurnOnReverse());
		SmartDashboard::PutData("Turn Tote CW", new IntakeCW());
		SmartDashboard::PutData("Turn Tote CCW", new IntakeCCW());
		SmartDashboard::PutData("Acquire Tote", new AcquireToteCommand());
//		SmartDashboard::PutData("ArmTop", new ArmGoToPositionCommand(ARM_PIVOT_POSITION_TOP));
//		SmartDashboard::PutData("ArmBot", new ArmGoToPositionCommand(ARM_PIVOT_POSITION_BOT));
		SmartDashboard::PutData("Zero Stacker Encoders", new StackerZeroEncodersCommand());
		SmartDashboard::PutData("Calibrate Arm Encoder Offsets", new CalibrateArmEncoderOffsetsCommand());

		SmartDashboard::PutData("Disable Right Lift", new StackerSetFeedbackCommand(Stacker::RIGHT, false));
		SmartDashboard::PutData("Enable Right Lift", new StackerSetFeedbackCommand(Stacker::RIGHT, true));
		SmartDashboard::PutData("Disable Left Lift", new StackerSetFeedbackCommand(Stacker::LEFT,false));
		SmartDashboard::PutData("Enable Left Lift", new StackerSetFeedbackCommand(Stacker::LEFT,true));

		SmartDashboard::PutData("Stacker Goto Top", new StackerGoToTopCommand());
		SmartDashboard::PutData("Stacker Goto Bottom", new StackerGoToBottomCommand());
		SmartDashboard::PutData("Stacker Goto Bottom Loaded", new StackerGoToBottomCommand(true));
		SmartDashboard::PutData("Stacker Goto Scoring Platform", new StackerGoToScoringPlatformCommand());

		SmartDashboard::PutNumber("IMU roll", CommandBase::driveTrain->GetRoll());
		SmartDashboard::PutNumber("IMU pitch", CommandBase::driveTrain->GetPitch());
		SmartDashboard::PutNumber("IMU heading", CommandBase::driveTrain->GetHeading());


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
//		CommandBase::stacker->PeriodicUpdate();
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
		CommandBase::intake->PeriodicUpdate();
		CommandBase::arm->PeriodicUpdate();

		SmartDashboard::PutNumber("POV Values", CommandBase::oi->GetAuxStick()->GetPOV());


	}

	void TestPeriodic()
	{
		lw->Run();
	}

	void Periodic(){
		CommandBase::stacker->PeriodicUpdate();
		CommandBase::intake->PeriodicUpdate();
	}
};

START_ROBOT_CLASS(Robot);

