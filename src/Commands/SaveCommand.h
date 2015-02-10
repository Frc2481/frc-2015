#ifndef SaveCommand_H
#define SaveCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class SaveCommand: public CommandBase
{
public:
	SaveCommand(){}
	void Initialize(){
		Preferences::GetInstance()->Save();
	}
	void Execute(){}
	bool IsFinished(){}
	void End(){}
	void Interrupted(){}
};

#endif
