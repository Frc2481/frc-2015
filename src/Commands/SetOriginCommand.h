#ifndef SetOriginCommand_H
#define SetOriginCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class SetOriginCommand: public CommandBase
{
private:
	double xPos;
	double yPos;
	double oldX;
	double oldY;

public:
	SetOriginCommand(double xPosition, double yPosition){
		xPos = xPosition;
		yPos = yPosition;
	}
	void Initialize(){
		oldX = CommandBase::driveTrain->GetXOrigin();
		oldY = CommandBase::driveTrain->GetYOrigin();
		CommandBase::driveTrain->SetOrigin(xPos, yPos);
	}
	void Execute(){}
	bool IsFinished(){
		return false;
	}
	void End(){
		CommandBase::driveTrain->SetOrigin(oldX, oldY);
	}
	void Interrupted(){
		End();
	}
};

#endif
