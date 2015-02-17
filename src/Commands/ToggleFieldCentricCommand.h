#ifndef TOGGLEFIELDCENTRICCOMMAND_H
#define TOGGLEFIELDCENTRICCOMMAND_H

#include "../CommandBase.h"

/**
 *
 *
 * @author ExampleAuthor
 */
class ToggleFieldCentricCommand : public CommandBase {
public:
	ToggleFieldCentricCommand(){
		
	}
	virtual void Initialize(){
		driveTrain->SetFieldCentric(true);
	}
	virtual void Execute(){
		
	}
	virtual bool IsFinished(){
		return false;
	}
	virtual void End(){
		driveTrain->SetFieldCentric(false);
	}
	virtual void Interrupted(){
		End();
	}
};

#endif
