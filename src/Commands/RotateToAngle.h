/*
 * RotateToAngle.h
 *
 *  Created on: Jan 16, 2015
 *      Author: thomasSpeciale
 */

#ifndef SRC_COMMANDS_ROTATETOANGLE_H_
#define SRC_COMMANDS_ROTATETOANGLE_H_

#include "../CommandBase.h"
#include "WPILib.h"

class RotateToAngle: public CommandBase
{
private:
	PIDController* PIDController2481;
	class PIDRotate : public PIDOutput{

		private:
			double value;

		public:
			PIDRotate(){
				value = 0.00;
			}

			float getValue (){
				return value;
			}

			void PIDWrite (float output){
				value = output;
			}
		};
	PIDRotate* rotate;
public:
	RotateToAngle(){}
	void Initialize(){
		rotate = new PIDRotate();
		PIDController2481 = new PIDController(0.01f,0.005f,0.0f, driveTrain->GetIMU(), rotate);
	}
	void Execute(){driveTrain->Crab(0.0,0.0,rotate->getValue());}
	bool IsFinished(){
		return PIDController2481->OnTarget();
	}
	void End(){
		delete rotate;
		delete PIDController2481;
	}
	void Interrupted(){
		End();
	}
};



#endif /* SRC_COMMANDS_ROTATETOANGLE_H_ */
