#ifndef WristTiltDownCommand_H
#define WristTiltDownCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class WristTiltDownCommand: public CommandBase
{
public:
	WristTiltDownCommand(){
		Requires(arm);
	}
	void Initialize(){
		arm->SetWristOffsetRelative(-5.0f);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){
		arm->StopPivotWrist();
	}
	void Interrupted(){
		End();
	}
};

#endif
