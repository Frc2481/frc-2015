#ifndef IntakeTurnOnReverse_H
#define IntakeTurnOnReverse_H

#include "../CommandBase.h"
#include "WPILib.h"

class IntakeTurnOnReverse: public CommandBase
{
private:
	double mSpeed;
public:
	IntakeTurnOnReverse(double speed = INTAKE_REVERSE_SPEED){
		Requires(intake);
		mSpeed = speed;
	}
	void Initialize(){
		CommandBase::intake->TurnOnReverse(mSpeed);
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		CommandBase::intake->TurnOff();
	}
	void Interrupted(){
		End();
	}
};

class IntakeTurnOnLeftReverse : public CommandBase {
public:
	IntakeTurnOnLeftReverse() {
		Requires(intake);
	}
	void Initialize(){
		CommandBase::intake->TurnOnLeftReverse();
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		CommandBase::intake->TurnOff();
	}
	void Interrupted(){
		End();
	}
};
#endif
