#ifndef CalibrateArmEncoderOffsetsCommand_H
#define CalibrateArmEncoderOffsetsCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class CalibrateArmEncoderOffsetsCommand: public CommandBase
{
public:
	CalibrateArmEncoderOffsetsCommand(){
		SetRunWhenDisabled(true);
	}
	void Initialize(){
		float wrist = arm->GetRawWristAngle();
		float shoulder = arm->GetRawShoulderAngle();

		arm->SetShoulderEncoderOffset(shoulder);
		arm->SetWristEncoderOffset(wrist);

		Preferences::GetInstance()->PutFloat("WRIST_ENCODER_OFFSET", wrist);
		Preferences::GetInstance()->PutFloat("SHOULDER_ENCODER_OFFSET", shoulder);

		Preferences::GetInstance()->Save();
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
