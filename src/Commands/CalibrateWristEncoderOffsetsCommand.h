#ifndef CalibrateWristEncoderOffsetsCommand_H
#define CalibrateWristEncoderOffsetsCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class CalibrateWristEncoderOffsetsCommand: public CommandBase
{
public:
	CalibrateWristEncoderOffsetsCommand(){
		SetRunWhenDisabled(true);
	}
	void Initialize(){
		double wrist = arm->GetRawWristAngle();

		arm->SetWristEncoderOffset(wrist - 180);

		PersistedSettings::GetInstance().Set("WRIST_ENCODER_OFFSET", wrist - 180);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
