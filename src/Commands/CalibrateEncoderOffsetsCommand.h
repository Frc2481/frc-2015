#ifndef CALIBRATE_ENCODER_OFFSETS_COMMAND_H
#define CALIBRATE_ENCODER_OFFSETS_COMMAND_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "../RobotParameters.h"
#include "Components/PersistedSettings.h"

class CalibrateEncoderOffsetsCommand: public CommandBase
{
public:
	CalibrateEncoderOffsetsCommand() {
		SetRunWhenDisabled(true);
	}
	void Initialize()
	{
		//set encoder value of front left swerve module
		saveAndApplyEncoderOffset(FRONT_LEFT_ENCODER, "FL_ENCODER_OFFSET");

		//set encoder value of front right swerve module
		saveAndApplyEncoderOffset(FRONT_RIGHT_ENCODER, "FR_ENCODER_OFFSET");

		//set encoder value of back left swerve module
		saveAndApplyEncoderOffset(BACK_LEFT_ENCODER, "BL_ENCODER_OFFSET");

		//set encoder value of back right swerve module
		saveAndApplyEncoderOffset(BACK_RIGHT_ENCODER, "BR_ENCODER_OFFSET");

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
		PersistedSettings::GetInstance().Set(key.c_str(),temp);
	}
};

#endif
