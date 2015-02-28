//#include <Commands/CalibrateEncoderOffsetsCommand.h>
#include <unistd.h>
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
#include "Commands/StackerZeroEncodersCommand.h"
#include "Commands/StackerGoToTopCommand.h"
#include "Commands/CalibrateEncoderOffsetsCommand.h"
#include "Commands/StackerDisableBrakeCommand.h"
#include "Commands/AcquireToteCommand.h"
#include "Commands/StackerGoToScoringPlatformCommand.h"
#include "Commands/PickUpToteToScoringPlatformCommand.h"
#include "Commands/CalibrateArmEncoderOffsetsCommand.h"
#include "Commands/ArmWristToSetPoint.h"
#include "Commands/ArmWristManual.h"
#include "Commands/ArmShoulderManual.h"
#include "Commands/ArmShoulderToSetPoint.h"
#include "Commands/ExtendSlideCommand.h"
#include "Commands/RetractSlideCommand.h"
#include "Commands/CalibrateShoulderEncoderOffsetsCommand.h"
#include "Commands/CalibrateWristEncoderOffsetsCommand.h"
#include "Commands/ArmWristResetStall.h"
#include "Commands/RemoveRCFromStepCommand.h"
#include "Commands/ThreeToteStackAutoCommandGroup.h"
#include "Commands/FishingPoleAutoCommandGroup.h"
#include "Commands/CastFishingPolesCommand.h"
#include "Commands/ReelFishingPolesCommand.h"
#include "Commands/ThreeToteStackAutoNoStrafeCommandGroup.h"
#include "Commands/ArmWristStalledMonitor.h"
#include "Commands/StackerStalledMonitor.h"

#include "RobotParameters.h"

using namespace std;
class Robot: public IterativeRobot
{
private:
	SendableChooser *autoOptions;
	Command *autonomousCommand;
	Command *armWristStalledMonitor;
	Command *stackerStalledMonitor;
	LiveWindow *lw;
	USBCamera* mCamera;

	void RobotInit()
	{
		CameraServer::GetInstance()->SetQuality(50);
		CameraServer::GetInstance()->SetSize(1);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
//		mCamera = new USBCamera("cam0", true);
//		mCamera->SetBrightness(50);
//		mCamera->SetExposureManual(50);

		//Auto Choosing
		autoOptions = new SendableChooser();

		autoOptions->AddObject("Three Tote Auto", new ThreeToteStackAutoCommandGroup());
		autoOptions->AddObject("Fishing Pole Auto", new FishingPoleAutoCommandGroup());
		autoOptions->AddObject("Three Tote Auto (No Can)", new ThreeToteStackAutoNoStrafeCommandGroup());
		//End Auto Choosing

		armWristStalledMonitor = new ArmWristStalledMonitor();
		armWristStalledMonitor->Start();

		stackerStalledMonitor = new StackerStalledMonitor();
		stackerStalledMonitor->Start();

		CommandBase::init();
		//autonomousCommand = new ThreeToteStackAutoCommand();
		lw = LiveWindow::GetInstance();

		SmartDashboard::PutData(Scheduler::GetInstance());
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

		SmartDashboard::PutData("Calibrate Shoulder Encoder Offsets", new CalibrateShoulderEncoderOffsetsCommand());
		SmartDashboard::PutData("Calibrate Wrist Encoder Offsets", new CalibrateWristEncoderOffsetsCommand());

		SmartDashboard::PutData("Reset Wrist Stalled", new ArmWristResetStall());

		SmartDashboard::PutData("Stacker Goto Top", new StackerGoToTopCommand());
		SmartDashboard::PutData("Stacker Goto Bottom", new StackerGoToBottomCommand());
		SmartDashboard::PutData("Stacker Goto Bottom Loaded", new StackerGoToBottomCommand(true));
		SmartDashboard::PutData("Stacker Goto Scoring Platform", new StackerGoToScoringPlatformCommand());

		SmartDashboard::PutNumber("IMU roll", CommandBase::driveTrain->GetRoll());
		SmartDashboard::PutNumber("IMU pitch", CommandBase::driveTrain->GetPitch());
		SmartDashboard::PutNumber("IMU heading", CommandBase::driveTrain->GetHeading());

		SmartDashboard::PutData("Wrist 180", new ArmWristToSetPoint(180));
		SmartDashboard::PutData("Wrist 90", new ArmWristToSetPoint(90));
		SmartDashboard::PutData("Wrist 270", new ArmWristToSetPoint(280));

		SmartDashboard::PutData("Wrist Down", new ArmWristManual(1));
		SmartDashboard::PutData("Wrist Up", new ArmWristManual(-1));

		SmartDashboard::PutData("Shoulder 1", new ArmShoulderManual(1));
		SmartDashboard::PutData("Shoulder -1", new ArmShoulderManual(-1));

		SmartDashboard::PutData("Shoulder 5", new ArmShoulderToSetPoint(0));
		SmartDashboard::PutData("Shoulder 99", new ArmShoulderToSetPoint(99));
		SmartDashboard::PutData("Shoulder 45", new ArmShoulderToSetPoint(45));
		SmartDashboard::PutData("shoulder 80", new ArmShoulderToSetPoint(85));
		SmartDashboard::PutData("shoulder 90", new ArmShoulderToSetPoint(90));
		SmartDashboard::PutData("shoulder 95", new ArmShoulderToSetPoint(95));

		SmartDashboard::PutData("Slide Extend", new ExtendSlideCommand());
		SmartDashboard::PutData("Slide Retract", new RetractSlideCommand());

		SmartDashboard::PutData("Get RC From Step", new RemoveRCFromStepCommand());

		SmartDashboard::PutData("Fishing Pole Auto", new FishingPoleAutoCommandGroup());

		SmartDashboard::PutData("Cast Fishing Pole", new CastFishingPolesCommand());
		SmartDashboard::PutData("Reel Fishing Pole", new ReelFishingPolesCommand());

		PersistedSettings::GetInstance().Set("STACKER_P", STACKER_P);
		PersistedSettings::GetInstance().Set("STACKER_I", STACKER_I);
		PersistedSettings::GetInstance().Set("STACKER_D", STACKER_D);
//		PersistedSettings::GetInstance().Set("I", STACKER_P);
//
//		PersistedSettings::GetInstance().Set("INTAKE_FORWARD_SPEED", .8);
//		PersistedSettings::GetInstance().Set("INTAKE_REVERSE_SPEED", .8);
//
//		PersistedSettings::GetInstance().Set("WRIST_P", .05);
//		PersistedSettings::GetInstance().Set("SHOULDER_P", .05);

		SmartDashboard::PutData("Three Tote Stack Auto", new ThreeToteStackAutoCommandGroup());
	}
	
	void DisabledPeriodic()
	{
		Scheduler::GetInstance()->Run();
		//CommandBase::driveTrain->Crab(0,-5,0);
	}

	void AutonomousInit()
	{
		autonomousCommand = new ThreeToteStackAutoCommandGroup();
		if (autonomousCommand != NULL)
			autonomousCommand->Start();

	}

	void AutonomousPeriodic()
	{
		Scheduler::GetInstance()->Run();
//		CommandBase::stacker->PeriodicUpdate();

		CommandBase::driveTrain->PeriodicUpdate();
		CommandBase::stacker->PeriodicUpdate();
		CommandBase::intake->PeriodicUpdate();
		CommandBase::arm->PeriodicUpdate();
		SmartDashboard::PutNumber("IMU heading", CommandBase::driveTrain->GetHeading());
	}

	void TeleopInit()
	{
		CommandBase::driveTrain->SetGyroCorrection(false);
		CommandBase::arm->SetWristLinked(false);
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

		SmartDashboard::PutNumber("IMU roll", CommandBase::driveTrain->GetRoll());
				SmartDashboard::PutNumber("IMU pitch", CommandBase::driveTrain->GetPitch());
				SmartDashboard::PutNumber("IMU heading", CommandBase::driveTrain->GetHeading());
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

