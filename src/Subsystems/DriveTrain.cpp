/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 9, 2014
 *      Author: johnnyBaurer
 *      Editor: thomasSpeciale
 */

#include <cmath>
#include <algorithm>
#include "DriveTrain.h"
#include "../RobotMap.h"
#include "Commands/DriveCommand.h"
#include "Components/PersistedSettings.h"


DriveTrain::DriveTrain() : Subsystem("DriveTrain"),
				FLWheel(new SwerveModule(FRONT_LEFT_DRIVE, FRONT_LEFT_STEER, FRONT_LEFT_ENCODER)),
				FRWheel(new SwerveModule(FRONT_RIGHT_DRIVE, FRONT_RIGHT_STEER, FRONT_RIGHT_ENCODER)),
				BRWheel(new SwerveModule(BACK_RIGHT_DRIVE, BACK_RIGHT_STEER, BACK_RIGHT_ENCODER)),
				BLWheel(new SwerveModule(BACK_LEFT_DRIVE, BACK_LEFT_STEER, BACK_LEFT_ENCODER)),
				serialPort(new SerialPort(57600,SerialPort::kMXP)),
				imu(new IMU(serialPort,update_rate_hz)),
				isFieldCentric(false),
				isForward(true),
				mXPos(0), mYPos(0), mTwist(0),
				mPIDGyro(new PIDController(0.1, 0.002, 0, NULL, NULL)){

	printf("Pre DriveTrain Constructor \n");
	prevAngle = 90.0;
	FLWheel->SetOffset(PersistedSettings::GetInstance().Get("FL_ENCODER_OFFSET", 181.561));
	FRWheel->SetOffset(PersistedSettings::GetInstance().Get("FR_ENCODER_OFFSET", 325.812));
	BRWheel->SetOffset(PersistedSettings::GetInstance().Get("BR_ENCODER_OFFSET", 348.182));
	BLWheel->SetOffset(PersistedSettings::GetInstance().Get("BL_ENCODER_OFFSET", 13.0601));
	//driveLogger = new DataLogger("/home/lvuser/DriveLogger.txt");
	gyroCorrection = false;

	originX = 0.0f;
	originY = 0.0f;

	bool is_calibrating = imu->IsCalibrating();
	if(!is_calibrating)
	{
		Wait(0.3);
		imu->ZeroYaw();
	}
	printf("post DriveTrain Constructor \n");

	SmartDashboard::PutData("GYRO PID",mPIDGyro);
}

void DriveTrain::InitDefaultCommand() {
	SetDefaultCommand(new DriveCommand());
}

void DriveTrain::Stop() {
	Crab(0,0,0);
}

void DriveTrain::CrabV2(double xPos, double yPos, double twist){
	double FWD;
	double STR;

	float gyroAngle = imu->GetYaw();

	//sanity check on Gyro, if Gyro angle is too far off ignore
	if(fabs(gyroAngle) > 50){
		gyroCorrection = false;
	}

	//stop Gryo from correcting while sitting still
	if (gyroCorrection) {
		if (xPos != 0 || yPos != 0) {

			//TODO: Decide if we want this.
			gyroAngle = std::max(std::min(gyroAngle, 10.0f), -10.0f);
			twist = gyroAngle / 30.0;
			printf("GYRO CORRECTION\n");
		}
	}


	twist = -twist;
	if (isFieldCentric) {
		heading = -gyroAngle;
		FWD = yPos * cos(heading * pi / 180) + xPos *sin(heading * pi / 180);
		STR = xPos * cos(heading * pi / 180) - yPos * sin(heading * pi / 180);
	}
	else {
		twist = twist * .4;   //limit twist speed while not in field centric
		FWD = yPos;
		STR = xPos;
	}
	if (isForward) {
		FWD = -FWD;
		STR = -STR;
	}
	else {

	}
	
//	SmartDashboard::PutNumber("FWD", FWD);
//	SmartDashboard::PutNumber("STR", STR);
//	SmartDashboard::PutNumber("twist", twist);
//	SmartDashboard::PutNumber("Gyro Angle", gyroAngle);

    double A = STR - twist * baseLength / radius;
	double B = STR + twist * baseLength / radius;
	double C = FWD - twist * baseWidth / radius;
	double D = FWD + twist * baseWidth / radius;
//	SmartDashboard::PutNumber("A", A);
//	SmartDashboard::PutNumber("B", B);
//	SmartDashboard::PutNumber("C", C);
//	SmartDashboard::PutNumber("D", D);
//	SmartDashboard::PutNumber("twist", twist);
	double wheelSpeedFL = sqrt(pow(B, 2) + pow(C, 2));
	double wheelSpeedFR = sqrt(pow(B, 2) + pow(D, 2));
	double wheelSpeedBL = sqrt(pow(A, 2) + pow(C, 2));
	double wheelSpeedBR = sqrt(pow(A, 2) + pow(D, 2));
	double wheelAngleFL = atan2(B, C) * 180 / pi;
	double wheelAngleFR = atan2(B, D) * 180 / pi;
	double wheelAngleBL = atan2(A, C) * 180 / pi;
	double wheelAngleBR = atan2(A, D) * 180 / pi;
	
	
	//speeds normalized 0 to 1
	//maybe eventually reverse motor instead of turning far and going forward
	double maxWheelSpeed = wheelSpeedFR;
	if (wheelSpeedFL > maxWheelSpeed) {
		maxWheelSpeed = wheelSpeedFL;
	}
	if (wheelSpeedBR > maxWheelSpeed) {
		maxWheelSpeed = wheelSpeedBR;
	}
	if (wheelSpeedBL > maxWheelSpeed) {
		maxWheelSpeed = wheelSpeedBL;
	}
	if (maxWheelSpeed > 1) {
		wheelSpeedFR /= maxWheelSpeed;
		wheelSpeedFL /= maxWheelSpeed;
		wheelSpeedBR /= maxWheelSpeed;
		wheelSpeedBL /= maxWheelSpeed;
	}
	
	SmartDashboard::PutNumber("wheelSpeedFR", wheelSpeedFR);
	SmartDashboard::PutNumber("wheelSpeedFL", wheelSpeedFL);
	SmartDashboard::PutNumber("wheelSpeedBR", wheelSpeedBR);
	SmartDashboard::PutNumber("wheelSpeedBL", wheelSpeedBL);

	SmartDashboard::PutNumber("wheelAngleFR", FRWheel->GetRawAngle());
	SmartDashboard::PutNumber("wheelAngleFRV", FRWheel->GetVoltage());

	SmartDashboard::PutNumber("wheelAngleFL", FLWheel->GetRawAngle());
	SmartDashboard::PutNumber("wheelAngleFLV", FLWheel->GetVoltage());

	SmartDashboard::PutNumber("wheelAngleBR", BRWheel->GetRawAngle());
	SmartDashboard::PutNumber("wheelAngleBRV", BRWheel->GetVoltage());

	SmartDashboard::PutNumber("wheelAngleBL", BLWheel->GetRawAngle());
	SmartDashboard::PutNumber("wheelAngleBLV", BLWheel->GetVoltage());

	SmartDashboard::PutNumber("aref", ControllerPower::GetVoltage5V());

	SmartDashboard::PutNumber("commandedAngleFR", wheelAngleFR);
	SmartDashboard::PutNumber("commandedAngleFL", wheelAngleFL);
	SmartDashboard::PutNumber("commandedAngleBR", wheelAngleBR);
	SmartDashboard::PutNumber("commandedAngleBL", wheelAngleBL);
	
	//if (fieldCentric) {
	/*
		float heading = headingSource->GetHeading();
		wheelAngleFR += heading;
		wheelAngleFL += heading;
		wheelAngleBR += heading;
		wheelAngleBL += heading;
		*/
	//}
	
	//printf("%f\n", FLWheel->GetAngle());
	//printf("setPoint  = %f\n",FLWheel->GetController()->GetSetPoint());
	FLWheel->Set(wheelSpeedFL, wheelAngleFL);
	FRWheel->Set(-wheelSpeedFR, wheelAngleFR);
	BRWheel->Set(-wheelSpeedBR, wheelAngleBR);
	BLWheel->Set(wheelSpeedBL, wheelAngleBL);


	
	//angleOffset = wheelAngleFL + 180;
	
	//printf("%f %f %f %f \n", FLWheel->GetRawAngle(), FRWheel->GetRawAngle(), BLWheel->GetRawAngle(), BRWheel->GetRawAngle());
}

void DriveTrain::SetLengthAndWidth(double robotLength, double robotWidth) {
	baseLength = robotLength;
	baseWidth = robotWidth;
	radius = sqrt(pow(robotLength, 2)+pow(robotWidth, 2));
}
//ToDo: move out to library
double DriveTrain::degToRad(double deg) {
	return deg * pi / 180;
}

double DriveTrain::radToDeg(double rad) {
	return rad * 180 / pi;
}

float DriveTrain::GetEncoderValue(int wheel) {
	if (wheel == FRONT_RIGHT_ENCODER) {
		return FRWheel->GetRawAngle();
	}else if (wheel == FRONT_LEFT_ENCODER) {
		return FLWheel->GetRawAngle();
	}else if (wheel == BACK_RIGHT_ENCODER) {
		return BRWheel->GetRawAngle();
	}else if (wheel == BACK_LEFT_ENCODER) {
		return BLWheel->GetRawAngle();
	}
	return 0.0;
}

void DriveTrain::SetEncoderOffset(int wheel, float offset){
	if (wheel == FRONT_RIGHT_ENCODER){
		FRWheel->SetOffset(offset);
	}else if (wheel == FRONT_LEFT_ENCODER){
		FLWheel->SetOffset(offset);
	}else if (wheel == BACK_RIGHT_ENCODER){
		BRWheel->SetOffset(offset);
	}else if (wheel == BACK_LEFT_ENCODER){
		BLWheel->SetOffset(offset);
	}
}

DriveTrain::~DriveTrain() {
	delete FRWheel;
	delete BRWheel;
	delete FLWheel;
	delete BLWheel;
}

float DriveTrain::GetP() { 
	return FLWheel->GetController()->GetP();
}

void DriveTrain::SetP(float p) {
	FLWheel->GetController()->SetP(p);
	FRWheel->GetController()->SetP(p);
	BRWheel->GetController()->SetP(p);
	BLWheel->GetController()->SetP(p);
}

float DriveTrain::GetI() { 
	return FLWheel->GetController()->GetI();
}

void DriveTrain::SetI(float i) {
	FLWheel->GetController()->SetI(i);
	FRWheel->GetController()->SetI(i);
	BRWheel->GetController()->SetI(i);
	BLWheel->GetController()->SetI(i);
}
void DriveTrain::ResetGyro(){
	printf("\n\n reset wii in driveTrain \n \n");
}

float DriveTrain::GetHeading(){
	heading = imu->GetYaw();
	return heading;
}

void DriveTrain::SetFieldCentric(bool fieldCentric) {
	isFieldCentric = fieldCentric;
}

float DriveTrain::GetWheelAngle(int wheel){
	if (wheel == FRONT_LEFT_ENCODER) 		return FLWheel->GetRawAngle();
	else if (wheel == FRONT_RIGHT_ENCODER) 	return FRWheel->GetRawAngle();
	else if (wheel == BACK_LEFT_ENCODER) 	return BLWheel->GetRawAngle();
	else if (wheel == BACK_RIGHT_ENCODER) 	return BRWheel->GetRawAngle();
	return 0;
}

void DriveTrain::SetWheelAngle(int wheel, float angle){
	if (wheel == FRONT_LEFT_ENCODER) 		FLWheel->Set(0, angle);
	else if (wheel == FRONT_RIGHT_ENCODER) 	FRWheel->Set(0, angle);
	else if (wheel == BACK_LEFT_ENCODER) 	BLWheel->Set(0, angle);
	else if (wheel == BACK_RIGHT_ENCODER) 	BRWheel->Set(0, angle);
}
void DriveTrain::SetOptimized(bool optimized){
	FLWheel->SetOptimized(optimized);
	FRWheel->SetOptimized(optimized);
	BLWheel->SetOptimized(optimized);
	BRWheel->SetOptimized(optimized);
}

void DriveTrain::SetForward(bool fwd) {
	isForward = fwd;
}

void DriveTrain::SetGyroCorrection(bool b) {
	gyroCorrection = b;
	ResetGyroAccumError();
}

void DriveTrain::ResetGyroAccumError()
{
	gyroAccumError = 0.0;
}

void DriveTrain::ZeroYaw() {
	imu->ZeroYaw();
}

bool DriveTrain::IsGyroCorrection() const {
	return gyroCorrection;
}

IMU* DriveTrain::GetIMU(){
	return imu;
}

void DriveTrain::Crab(double xPos, double yPos, double twist) {
	mXPos = xPos;
	mYPos = yPos;
	mTwist = twist;

	double FWD;
	double STR;

		float gyroAngle = imu->GetYaw();

		//sanity check on Gyro, if Gyro angle is too far off ignore
		if(fabs(gyroAngle) > 50){
			//gyroCorrection = false;
		}

		//stop Gryo from correcting while sitting still
		if (gyroCorrection) {

				//TODO: Decide if we want this.
			if (xPos != 0 || yPos != 0) {
				gyroAngle = std::max(std::min(-gyroAngle, 30.0f), -30.0f);
				gyroAccumError += (gyroAngle * 2.0);
				gyroAccumError = std::max(std::min(gyroAccumError, 5.0), -5.0);
				float P = mPIDGyro->GetP();
				float I = mPIDGyro->GetI() * .1;
				twist = gyroAngle * P + gyroAccumError * I;
				printf("GYRO CORRECTION %f \n", gyroAngle);
				SmartDashboard::PutBoolean("GYRO Correction 2", true);
				SmartDashboard::PutNumber("Gyro I Accum", gyroAccumError);

				twist *= sqrt((xPos * xPos) + (yPos * yPos));
				twist *= 2;
				twist = std::max(std::min(twist, .1), -.1);
				SmartDashboard::PutNumber("GYRO Twist Correct", twist);
			}


//			} else {
			//	SmartDashboard::PutBoolean("GYRO Correction 2", false);
			//}
		}



		SmartDashboard::PutBoolean("GYRO Correction", gyroCorrection);


		twist = -twist;
		if (isFieldCentric) {
			heading = -gyroAngle;
			FWD = yPos * cos(heading * pi / 180) + xPos *sin(heading * pi / 180);
			STR = xPos * cos(heading * pi / 180) - yPos * sin(heading * pi / 180);
		}
		else {
			twist = twist * .05;   //limit twist speed while not in field centric
			FWD = yPos;
			STR = xPos;
		}
		if (isForward) {
			FWD = -FWD;
			STR = -STR;
		}
		else {

		}
		if(fabs(originX) > 0.1f || fabs(originY) > 0.1f){
			twist *= -1;
		}
	//	SmartDashboard::PutNumber("FWD", FWD);
	//	SmartDashboard::PutNumber("STR", STR);
	//	SmartDashboard::PutNumber("twist", twist);
	//	SmartDashboard::PutNumber("Gyro Angle", gyroAngle);

		//Above mathematics, converted to use the same A,B,C,D pairs on each wheel as the working version with fixed pivot -JE
	    double A = STR - twist * ((baseLength / 2.0)+originY);
		double B = STR + twist * ((baseLength / 2.0)-originY);
		double C = FWD - twist * ((baseWidth / 2.0)+originX);
		double D = FWD + twist * ((baseWidth / 2.0)-originX);
	//	SmartDashboard::PutNumber("A", A);
	//	SmartDashboard::PutNumber("B", B);
	//	SmartDashboard::PutNumber("C", C);
	//	SmartDashboard::PutNumber("D", D);
	//	SmartDashboard::PutNumber("twist", twist);
		double wheelSpeedFL = sqrt(pow(B, 2) + pow(C, 2));
		double wheelSpeedFR = sqrt(pow(B, 2) + pow(D, 2));
		double wheelSpeedBL = sqrt(pow(A, 2) + pow(C, 2));
		double wheelSpeedBR = sqrt(pow(A, 2) + pow(D, 2));
		double wheelAngleFL = atan2(B, C) * 180 / pi;
		double wheelAngleFR = atan2(B, D) * 180 / pi;
		double wheelAngleBL = atan2(A, C) * 180 / pi;
		double wheelAngleBR = atan2(A, D) * 180 / pi;


		//speeds normalized 0 to 1
		//maybe eventually reverse motor instead of turning far and going forward
		double maxWheelSpeed = wheelSpeedFR;
		if (wheelSpeedFL > maxWheelSpeed) {
			maxWheelSpeed = wheelSpeedFL;
		}
		if (wheelSpeedBR > maxWheelSpeed) {
			maxWheelSpeed = wheelSpeedBR;
		}
		if (wheelSpeedBL > maxWheelSpeed) {
			maxWheelSpeed = wheelSpeedBL;
		}
		if (maxWheelSpeed > 1) {
			wheelSpeedFR /= maxWheelSpeed;
			wheelSpeedFL /= maxWheelSpeed;
			wheelSpeedBR /= maxWheelSpeed;
			wheelSpeedBL /= maxWheelSpeed;
		}

		SmartDashboard::PutNumber("wheelSpeedFR", wheelSpeedFR);
		SmartDashboard::PutNumber("wheelSpeedFL", wheelSpeedFL);
		SmartDashboard::PutNumber("wheelSpeedBR", wheelSpeedBR);
		SmartDashboard::PutNumber("wheelSpeedBL", wheelSpeedBL);

		SmartDashboard::PutNumber("wheelAngleFR", FRWheel->GetRawAngle());
		SmartDashboard::PutNumber("wheelAngleFRV", FRWheel->GetVoltage());

		SmartDashboard::PutNumber("wheelAngleFL", FLWheel->GetRawAngle());
		SmartDashboard::PutNumber("wheelAngleFLV", FLWheel->GetVoltage());

		SmartDashboard::PutNumber("wheelAngleBR", BRWheel->GetRawAngle());
		SmartDashboard::PutNumber("wheelAngleBRV", BRWheel->GetVoltage());

		SmartDashboard::PutNumber("wheelAngleBL", BLWheel->GetRawAngle());
		SmartDashboard::PutNumber("wheelAngleBLV", BLWheel->GetVoltage());

		SmartDashboard::PutNumber("aref", ControllerPower::GetVoltage5V());

		SmartDashboard::PutNumber("commandedAngleFR", wheelAngleFR);
		SmartDashboard::PutNumber("commandedAngleFL", wheelAngleFL);
		SmartDashboard::PutNumber("commandedAngleBR", wheelAngleBR);
		SmartDashboard::PutNumber("commandedAngleBL", wheelAngleBL);

		/*std::stringstream logstr;
		logstr << wheelAngleFL << "," << FLWheel->GetAngle() << ",";
		logstr << wheelAngleFR << "," << FRWheel->GetAngle() << ",";
		logstr << wheelAngleBL << "," << BLWheel->GetAngle() << ",";
		logstr << wheelAngleBR << "," << BRWheel->GetAngle();

		driveLogger->LogString(logstr.str());*/

		//if (fieldCentric) {
		/*
			float heading = headingSource->GetHeading();
			wheelAngleFR += heading;
			wheelAngleFL += heading;
			wheelAngleBR += heading;
			wheelAngleBL += heading;
			*/
		//}

		//printf("%f\n", FLWheel->GetAngle());
		//printf("setPoint  = %f\n",FLWheel->GetController()->GetSetPoint());
		FLWheel->Set(wheelSpeedFL, wheelAngleFL);
		FRWheel->Set(-wheelSpeedFR, wheelAngleFR);
		BRWheel->Set(-wheelSpeedBR, wheelAngleBR);
		BLWheel->Set(wheelSpeedBL, wheelAngleBL);



		//angleOffset = wheelAngleFL + 180;

		//printf("%f %f %f %f \n", FLWheel->GetRawAngle(), FRWheel->GetRawAngle(), BLWheel->GetRawAngle(), BRWheel->GetRawAngle());
}

void DriveTrain::SetOrigin(double xPos, double yPos) {
	originX = xPos;
	originY = yPos;
}

double DriveTrain::GetXOrigin() {
	return originX;
}

double DriveTrain::GetYOrigin() {
	return originY;
}

float DriveTrain::GetRoll() {
	roll = imu->GetRoll();
	return roll;
}

float DriveTrain::GetPitch() {
	pitch = imu->GetPitch();
	return pitch;
}

void DriveTrain::PeriodicUpdate() {
	Crab(mXPos, mYPos, mTwist);
}

void DriveTrain::SetBrake(bool brake) {
	FLWheel->SetBrake(brake);
	FRWheel->SetBrake(brake);
	BLWheel->SetBrake(brake);
	BRWheel->SetBrake(brake);
}
