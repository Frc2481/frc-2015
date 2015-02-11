#ifndef WristTiltUpCommand_H
#define WristTiltUpCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class WristTiltUpCommand: public CommandBase
{
public:
	WristTiltUpCommand(){
		Requires(arm);
	}
	void Initialize(){
		arm->SetWristOffsetRelative(5.0f);
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
