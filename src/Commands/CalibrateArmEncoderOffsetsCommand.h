#ifndef CalibrateArmEncoderOffsetsCommand_H
#define CalibrateArmEncoderOffsetsCommand_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "Components/PersistedSettings.h"

class CalibrateArmEncoderOffsetsCommand: public CommandBase
{
public:
	CalibrateArmEncoderOffsetsCommand(){
		SetRunWhenDisabled(true);
	}
	void Initialize(){
		double shoulder = arm->GetRawShoulderAngle();
		double wrist = arm->GetRawWristAngle();

		arm->SetShoulderEncoderOffset(shoulder);
		arm->SetWristEncoderOffset(wrist - 180);

		PersistedSettings::GetInstance().Set("WRIST_ENCODER_OFFSET", wrist - 180);
		PersistedSettings::GetInstance().Set("SHOULDER_ENCODER_OFFSET", shoulder);

	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
