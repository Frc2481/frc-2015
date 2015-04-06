/*
 * DigitalInputTrigger.h
 *
 *  Created on: Apr 2, 2015
 *      Author: Team2481
 */

#ifndef SRC_COMPONENTS_DIGITALINPUTTRIGGER_H_
#define SRC_COMPONENTS_DIGITALINPUTTRIGGER_H_
#include "WPILib.h"

class DigitalInputTrigger : public Trigger{
private:
	DigitalInput *mTrigger;
public:
	DigitalInputTrigger(DigitalInput *trigger);
	virtual ~DigitalInputTrigger();

	bool Get();

};

#endif /* SRC_COMPONENTS_DIGITALINPUTTRIGGER_H_ */
