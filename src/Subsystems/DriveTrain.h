/*
 * DriveTrain.h
 *
 *  Created on: Jan 9, 2014
 *      Author: Team2481
 */

#ifndef DRIVETRAIN_H_
#define DRIVETRAIN_H_
#include "../RobotParameters.h"
#include "../Components/SwerveModule.h"
#include "WPILib.h"
#include "Commands/Subsystem.h"
#include "../IMU/IMU.h"
#include "../Components/DataLogger.h"

class DriveTrain: public Subsystem {

#define MAX_CHANGE 10
private:
	SwerveModule *FLWheel;
	SwerveModule *FRWheel;
	SwerveModule *BRWheel;
	SwerveModule *BLWheel;
	uint8_t update_rate_hz = 50;
	SerialPort* serialPort;
	IMU* imu;
	DataLogger* driveLogger;
	const double pi = 3.14159;
	double baseWidth;
	double baseLength;
	double prevAngle;
	double radius;
	float prevAngleFR;
	float prevAngleFL;
	float prevAngleBR;
	float prevAngleBL;
	float angleOffset;
	float heading;
	float roll;
	float pitch;
	double gyroAccumError = 0;
	double gyroCorrectionOffset = 0;
	float originX;
	float originY;

	bool isFieldCentric;
	bool isForward;
	bool gyroCorrection;
	double mXPos, mYPos, mTwist;
public:
	DriveTrain();
	virtual ~DriveTrain();
	void InitDefaultCommand();
	void Crab(double xPos, double yPos, double twist);
	void CrabV2(double xPos, double yPos, double twist);    // Work in progress
	double degToRad(double deg);
	double radToDeg(double rad);
	double limitAngle(double angle);
	void SetLengthAndWidth(double robotLength, double robotWidth);
	void SetOrigin(double xPos, double yPos);
	double GetXOrigin();
	double GetYOrigin();
	float GetEncoderValue(int wheel);
	void SetEncoderOffset(int wheel, float offset);
	void SetP(float p);
	float GetP();
	void SetI(float i);
	float GetI();
	void ResetGyro();
	float GetHeading();
	float GetRoll();
	float GetPitch();
	double GetGyroCorrectionOffset();
	void Stop();
	void SetFieldCentric(bool fieldCentric);
	float GetWheelAngle(int wheel);
	void SetWheelAngle(int wheel, float angle);
	void SetOptimized(bool optimized);
	void SetForward(bool fwd);
	void SetGyroCorrection(bool b);
	void SetGyroCorrectionOffset(double offset);
	void ResetGyroAccumError();
	void ZeroYaw();
	bool IsGyroCorrection() const;
	IMU* GetIMU();
	void PeriodicUpdate();
	void SetBrake(bool brake);
};

#endif /* DRIVETRAIN_H_ */
