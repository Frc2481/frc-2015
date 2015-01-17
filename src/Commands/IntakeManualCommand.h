/*
 * IntakeManualCommand.h
 *
 *  Created on: Jan 16, 2015
 *      Author: thomasSpeciale
 */

#ifndef SRC_COMMANDS_INTAKEMANUALCOMMAND_H_
#define SRC_COMMANDS_INTAKEMANUALCOMMAND_H_

#include "../CommandBase.h"
#include "WPILib.h"
#include "Subsystems/Intake.h"

class IntakeManualCommand: public CommandBase
{
public:
	IntakeManualCommand(){
		Requires(intake);
	}
	void Initialize(){}
	void Execute(){
		float xValue = CommandBase::oi->GetAuxStick()->GetX();
		CommandBase::intake->IntakeManual(xValue);
	}
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



#endif /* SRC_COMMANDS_INTAKEMANUALCOMMAND_H_ */
