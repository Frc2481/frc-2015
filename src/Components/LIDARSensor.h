/*
 * LIDARSensor.h
 *
 *  Created on: Jan 30, 2015
 *      Author: Team2481
 */

#ifndef SRC_COMPONENTS_LIDARSENSOR_H_
#define SRC_COMPONENTS_LIDARSENSOR_H_

#include <PIDSource.h>
#include "WPILib.h"

class Notifier;

class LIDARSensor: public PIDSource {
private:
	I2C* i2c;
	char* distance;
	Notifier* readerThread;

	const uint8_t LIDAR_ADDR = 0x62;
	const uint8_t LIDAR_CONFIG_REGISTER = 0x00;
	const uint8_t LIDAR_DISTANCE_REGISTER = 0x8f;
public:
	LIDARSensor(I2C::Port port);
	virtual ~LIDARSensor();

	int getDistance();
	double pidGet();
	void start();
	void start(int period);
	void stop();
	static void CallUpdate(void *sensor);
	void update();
};

#endif /* SRC_COMPONENTS_LIDARSENSOR_H_ */
