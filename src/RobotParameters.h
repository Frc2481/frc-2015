#ifndef ROBOT_PARAMETERS_H
#define ROBOT_PARAMETERS_H
#include "Components/PersistedSettings.h"
#define DEBUGGING 1
#define ROBOT_SETTING_PATH "settings.cfg"
#define ENCODER_OFFSET_FILENAME "/home/lvuser/Encoder_Offsets"

//Robot Base
	#define ROBOT_LENGTH 30.75
	#define ROBOT_WIDTH 23.125

//CAN IDs
	//DriveTrain
		#define FRONT_LEFT_DRIVE 1
		#define FRONT_LEFT_STEER 2
		#define FRONT_RIGHT_DRIVE 3
		#define FRONT_RIGHT_STEER 4
		#define BACK_LEFT_DRIVE 5
		#define BACK_LEFT_STEER 6
		#define BACK_RIGHT_DRIVE 7
		#define BACK_RIGHT_STEER 8

	//Stacker
		#define LEFT_STACKER 10
		#define RIGHT_STACKER 9

	//Intake
		#define INTAKE_LEFT 11
		#define INTAKE_RIGHT 12

	//Arm
		#define ARM_SHOULDER_PIVOT 13
		#define ARM_WRIST_PIVOT 14

//Analog Channels
	#define FRONT_LEFT_ENCODER 0
	#define FRONT_RIGHT_ENCODER 1
	#define BACK_LEFT_ENCODER 2
	#define BACK_RIGHT_ENCODER 3

//Intake Define
	#define INTAKE_FORWARD_SPEED 1 * -1
	#define INTAKE_REVERSE_SPEED 1
	#define INTAKE_TRIM .5
	#define INTAKE_CONTAIN_LIMIT 4

//Arm Define
	#define ARM_PIVOT_POSITION_TOP 1
	#define ARM_PIVOT_POSITION_BOT 98

	#define SHOULDER_P .006
	#define WRIST_P .002

	#define SHOULDER_ENCODER 4
	#define WRIST_ENCODER 5

	#define EXTENTION_SOLENOID 1
	#define GRIPPER_SOLENOID 2

//Stacker Define
	#define STACKER_POSITION_UP 10981
	#define STACKER_POSITION_DOWN 1600
	#define STACKER_TICKS_PER_INCH 578
	//#define STACKER_LEFT_BOTTOM_LIMIT 2
	#define STACKER_RIGHT_BOTTOM_LIMIT 0
	//#define STACKER_LEFT_TOP_LIMIT 3
	#define STACKER_RIGHT_TOP_LIMIT 1
	#define STACKER_UP_SPEED PersistedSettings::GetInstance().Get("STACKER_UP_SPEED")
	#define STACKER_DOWN_SPEED PersistedSettings::GetInstance().Get("STACKER_DOWN_SPEED") * -1
	#define STACKER_BRAKE 0
	#define STACKER_ENCODER_A 2
	#define STACKER_ENCODER_B 3

	#define THREE_TOTE_AUTO_STACK_TIMEOUT 5.0
	#define STEP_HEIGHT 5.0

	#define ABOVE_STEP_HEIGHT 10.0

	#define STACKER_P .0002
	#define STACKER_I .0002
	#define STACKER_D .00001

//Slide Define
#define EXTENDER_SOLENOID 3
//FishingPole Define
	#define FISHING_POLE_SOLENOID 4

//Tote Count
	#define TOTE_COUNT_1_CURRENT_THRESHOLD 40
	#define TOTE_COUNT_2_CURRENT_THRESHOLD 60
	#define TOTE_COUNT_3_CURRENT_THRESHOLD 75
	#define TOTE_COUNT_4_CURRENT_THRESHOLD 85
	#define TOTE_COUNT_5_CURRENT_THRESHOLD 100
	#define TOTE_COUNT_6_CURRENT_THRESHOLD 130

#endif
