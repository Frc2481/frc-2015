#ifndef CalibrateShoulderEncoderOffsetsCommand_H
#define CalibrateShoulderEncoderOffsetsCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class CalibrateShoulderEncoderOffsetsCommand: public CommandBase
{
public:
	CalibrateShoulderEncoderOffsetsCommand(){
		SetRunWhenDisabled(true);
	}
	void Initialize(){
		double shoulder = arm->GetRawShoulderAngle();

		arm->SetShoulderEncoderOffset(shoulder);

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
