#ifndef ArmGripperShudderCommand_H
#define ArmGripperShudderCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class ArmGripperShudderCommand: public CommandBase
{
public:
	ArmGripperShudderCommand(){
	}
	void Initialize(){
		arm->SetGripperShudder(true);
	}
	void Execute(){

	}
	bool IsFinished(){
		return false;
	}
	void End(){
		arm->SetGripperShudder(false);
		arm->CloseGripper();
	}
	void Interrupted(){
		End();
	}
};

#endif
