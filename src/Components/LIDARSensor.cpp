/*
 * LIDARSensor.cpp
 *
 *  Created on: Jan 30, 2015
 *      Author: Team2481
 */

#include <Components/LIDARSensor.h>
#include "Notifier.h"
#include <unistd.h>

LIDARSensor::LIDARSensor(I2C::Port port) {
	i2c = new I2C(port, LIDAR_ADDR);
	distance = new char[2];
	readerThread = new Notifier(LIDARSensor::CallUpdate, this);
}

LIDARSensor::~LIDARSensor() {
	delete i2c;
	delete distance;
	delete readerThread;
}

int LIDARSensor::getDistance() {
	return (int)(distance[0] << 8) + (int)(distance[1]);
}

double LIDARSensor::pidGet() {
	return getDistance();
}

void LIDARSensor::start() {
	readerThread->StartPeriodic(0.1); //0.1 seconds = 100 ms
}

void LIDARSensor::start(int period) {
	readerThread->StartPeriodic(period);
}

void LIDARSensor::stop() {
	readerThread->Stop();
}

void LIDARSensor::CallUpdate(void *sensor)
{
	LIDARSensor* sens = (LIDARSensor*) sensor;
	sens->update();
}

void LIDARSensor::update() {
	i2c->Write(LIDAR_CONFIG_REGISTER, 0x04); // Initiate measurement
	sleep(0.04); // Delay for measurement to be taken
	i2c->Read(LIDAR_DISTANCE_REGISTER, 2, (uint8_t*)&distance); // Read in measurement
	sleep(0.005); // Delay to prevent over polling
}

