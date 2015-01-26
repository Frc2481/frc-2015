#ifndef CALIBRATE_ENCODER_OFFSETS_COMMAND_H
#define CALIBRATE_ENCODER_OFFSETS_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "../RobotParameters.h"

class CalibrateEncoderOffsetsCommand: public CommandBase
{
public:
	CalibrateEncoderOffsetsCommand() {}
	void Initialize()
	{
		//set encoder value of front left swerve module
		saveAndApplyEncoderOffset(FRONT_LEFT_ENCODER, "FRONT_LEFT_ENCODER");

		//set encoder value of front right swerve module
		saveAndApplyEncoderOffset(FRONT_RIGHT_ENCODER, "FRONT_RIGHT_ENCODER");

		//set encoder value of back left swerve module
		saveAndApplyEncoderOffset(BACK_LEFT_ENCODER, "BACK_LEFT_ENCODER");

		//set encoder value of back right swerve module
		saveAndApplyEncoderOffset(BACK_RIGHT_ENCODER, "BACK_RIGHT_ENCODER");

	}
	void Execute() {}
	bool IsFinished() {
		return true;
	}
	void End() {}
	void Interrupted() {}

private:
	void saveAndApplyEncoderOffset(int encoder, const std::string& key) {
		float temp = driveTrain->GetEncoderValue(encoder);
		driveTrain->SetEncoderOffset(encoder, temp);
		Preferences::GetInstance()->PutFloat(key.c_str(),temp);
	}
};

#endif
