/*
 * DigitalInputTrigger.cpp
 *
 *  Created on: Apr 2, 2015
 *      Author: Team2481
 */

#include <Components/DigitalInputTrigger.h>

DigitalInputTrigger::DigitalInputTrigger(DigitalInput *trigger) {
	// TODO Auto-generated constructor stub
	mTrigger = trigger;
}

DigitalInputTrigger::~DigitalInputTrigger() {
	// TODO Auto-generated destructor stub
}

bool DigitalInputTrigger::Get() {
	return mTrigger->Get();
}
