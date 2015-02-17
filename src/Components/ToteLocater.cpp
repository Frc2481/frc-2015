/*
 * ToteLocater.cpp
 *
 *  Created on: Feb 15, 2015
 *      Author: Team2481
 */

#include <Components/ToteLocater.h>

ToteLocator::ToteLocator() {
	pthread_mutex_init(&mMutex, NULL);
	pthread_create(&mThread,NULL,&ToteLocator::ThreadStarter, (void*)this);


}

ToteLocator::~ToteLocator() {
	// TODO Auto-generated destructor stub
	pthread_mutex_destroy(&mMutex);
}

void* ToteLocator::ThreadStarter(void* tl)
{
	ToteLocator* tl_obj = (ToteLocator*)tl;
	tl_obj->Execute();
	return tl;
}

void ToteLocator::Execute()
{
	bool running = true;
	bool connection = false;
	int status;
	darkPriest client;

	//std::cout << "initializing" << std::endl;
	status = client.initialize();

	if(status == -1)
	//cout << "error: " << errno << endl;

	while(running == true){

		//std::cout << "connecting" << std::endl;
		status = client.connecter();

		if(status == -1)
		//cout << "error: " << errno << endl;

		if(status == 0)
		connection = true;

		do{
			sleep(1);
		//	std::cout << "revieve data" << std::endl;
			status = client.revieve_data();
			if(status == -1)
		//	cout << "error: " << errno << endl;

		//	cout << client.dataStruct.angle << "  " << client.dataStruct.x << "  " << client.dataStruct.y << endl;
			if(status == 1)
			connection = false;
			pthread_mutex_lock(&mMutex);
			mX = client.dataStruct.x;
			mY = client.dataStruct.y;
			mAngle = client.dataStruct.angle;
			pthread_mutex_unlock(&mMutex);
		}while (connection == true);

	}
	//std::cout << "shut down" << std::endl;
	client.shut_down();
}
uint32_t ToteLocator::GetX() {
	uint32_t x;
	pthread_mutex_lock(&mMutex);
	x = mX;
	pthread_mutex_unlock(&mMutex);
	return x; //pSemaphore(initializeMutexNormal())
}

uint32_t ToteLocator::GetY() {
	uint32_t y;
	pthread_mutex_lock(&mMutex);
	y = mY;
	pthread_mutex_unlock(&mMutex);
	return y;
}

uint32_t ToteLocator::GetAngle() {
	uint32_t angle;
	pthread_mutex_lock(&mMutex);
	angle = mAngle;
	pthread_mutex_unlock(&mMutex);
	return angle;
}
