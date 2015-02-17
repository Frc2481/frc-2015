/*
 * ToteLocater.h
 *
 *  Created on: Feb 15, 2015
 *      Author: Team2481
 */

#ifndef SRC_COMPONENTS_TOTELOCATOR_H_
#define SRC_COMPONENTS_TOTELOCATOR_H_

#include <errno.h>
#include <pthread.h>
#include <DarkPriest/darkPriest.h>

class ToteLocator {
private:
	uint32_t mAngle;
	uint32_t mY;
	uint32_t mX;
	pthread_mutex_t mMutex;
	pthread_t mThread;

public:
	ToteLocator();
	virtual ~ToteLocator();
	uint32_t GetX();
	uint32_t GetY();
	static void* ThreadStarter(void* tl);
	void Execute();
	uint32_t GetAngle();
};

#endif /* SRC_COMPONENTS_TOTELOCATER_H_ */
