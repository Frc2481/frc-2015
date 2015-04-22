#ifndef SETFIELDCENTRICCOMMAND_H
#define SETFIELDCENTRICCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class SetFieldCentricCommand : public CommandBase {
private:
	bool mVal;
public:
	SetFieldCentricCommand(bool val){
		mVal = val;
	}
	virtual void Initialize(){
		driveTrain->SetFieldCentric(mVal);
	}
	virtual void Execute(){
		
	}
	virtual bool IsFinished(){
		return true;
	}
	virtual void End(){
	}
	virtual void Interrupted(){
		End();
	}
};

#endif
