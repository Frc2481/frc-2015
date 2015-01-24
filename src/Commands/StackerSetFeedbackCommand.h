#ifndef SetStackerFeedbackCommand_H
#define SetStackerFeedbackCommand_H

#include "../CommandBase.h"
#include "WPILib.h"
#include "../Subsystems/Stacker.h"

class StackerSetFeedbackCommand: public CommandBase
{
private:
	Stacker::StackerLiftID mID;
	bool mState;
public:
	enum StackerLiftID{
		RIGHT,
		LEFT,
	};
	StackerSetFeedbackCommand(Stacker::StackerLiftID id, bool state)
		: mID(id), mState(state){

	}
	void Initialize(){
		CommandBase::stacker->SetFeedbackEnable(mID, mState);
	}
	void Execute(){}
	bool IsFinished(){
		return true;
	}
	void End(){}
	void Interrupted(){}
};

#endif
