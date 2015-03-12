#ifndef StackerGoToPositionCommand_H
#define StackerGoToPositionCommand_H

#include "../CommandBase.h"
#include "WPILib.h"

class StackerGoToPositionCommand: public CommandBase
{
private:
	float mPosition;
	bool mDown;
public:
	StackerGoToPositionCommand(float pos)
	:mPosition(pos){
	}
	virtual void Initialize(){
		stacker->SetPosition(mPosition);
		if (stacker->GetPosition() > mPosition * 578) {
			mDown = true;
		} else {
			mDown = false;
		}
		stacker->Enable();
	}
	void Execute(){}
	virtual bool IsFinished(){
		if (mDown && stacker->GetPosition() < (mPosition * 578))
			return true;
		if (!mDown && stacker->GetPosition() > (mPosition * 578))
			return true;
		return false;
	}
	virtual void End(){
		stacker->Disable();
	}
	void Interrupted(){
		End();
	}
};

class StackerGoToPositionAboveStepHeightCommand : public StackerGoToPositionCommand {
private:
	bool mFromTop;
public:
	StackerGoToPositionAboveStepHeightCommand(float pos) : StackerGoToPositionCommand(pos){

	}

	void Initialize() {
		if (stacker->GetPosition() > (ABOVE_STEP_HEIGHT * 578)) {
			stacker->Enable(false);
			mFromTop = true;
		} else {
			StackerGoToPositionCommand::Initialize();
			mFromTop = false;
		}
	}

	bool IsFinished() {
		if (mFromTop) {
			return stacker->GetPosition() < ((ABOVE_STEP_HEIGHT * 578) + 200);
		} else {
			return StackerGoToPositionCommand::IsFinished();
		}
	}

	void End() {
		StackerGoToPositionCommand::End();

		if (mFromTop) {
			CommandGroup* g = GetGroup();
			if (g != NULL){
				g->Cancel();
			}
		}
	}
};

#endif
