/*
 * DriveTrain.cpp
 *
 *  Created on: Jan 9, 2014
 *      Author: johnny
 *      Editor: thomasSpeciale
 */

#include <cmath>
#include <algorithm>
#include "DriveTrain.h"
#include "../RobotMap.h"


DriveTrain::DriveTrain() : Subsystem("DriveTrain"),
				FLWheel(new SwerveModule(FRONT_LEFT_DRIVE, FRONT_LEFT_STEER, FRONT_LEFT_ENCODER)),
				FRWheel(new SwerveModule(FRONT_RIGHT_DRIVE, FRONT_RIGHT_STEER, FRONT_RIGHT_ENCODER)),
				BRWheel(new SwerveModule(BACK_RIGHT_DRIVE, BACK_RIGHT_STEER, BACK_RIGHT_ENCODER)),
				BLWheel(new SwerveModule(BACK_LEFT_DRIVE, BACK_LEFT_STEER, BACK_LEFT_ENCODER)),
				serialPort(new SerialPort(57600,SerialPort::kMXP)),
				imu(new IMU(serialPort,update_rate_hz)),
				isFieldCentric(false),
				isForward(true) {

	printf("Pre DriveTrain Constructor \n");
	prevAngle = 90.0;
	FLWheel->SetOffset(Preferences::GetInstance()->GetFloat("FL_ENCODER_OFFSET"));
	FRWheel->SetOffset(Preferences::GetInstance()->GetFloat("FR_ENCODER_OFFSET"));
	BRWheel->SetOffset(Preferences::GetInstance()->GetFloat("BR_ENCODER_OFFSET"));
	BLWheel->SetOffset(Preferences::GetInstance()->GetFloat("BL_ENCODER_OFFSET"));
	gyroCorrection = false;

	bool is_calibrating = imu->IsCalibrating();
	if(!is_calibrating)
	{
		Wait(0.3);
		imu->ZeroYaw();
	}
	printf("post DriveTrain Constructor \n");
}

void DriveTrain::InitDefaultCommand() {
//	SetDefaultCommand(new CrabDriveCommand());
}

void DriveTrain::Stop() {
	Crab(0,0,0);
}

void DriveTrain::Crab(double xPos, double yPos, double twist){
	double FWD;
	double STR;

	float gyroAngle = imu->GetYaw();

	//sanity check on Gyro, if Gyro angle is too far off ignore
	if(fabs(gyroAngle) > 50){
		gyroCorrection = false;
	}

	printf("Xpos: %f  YPos:  %f  Twist: %f Command: %s Gyro: %f\n", xPos, yPos, twist, GetCurrentCommand()->GetName().c_str(), gyroAngle);

	//stop Gryo from correcting while sitting still
	if (gyroCorrection) {
		if (xPos != 0 || yPos != 0) {

			//TODO: Decide if we want this.
			gyroAngle = std::max(std::min(gyroAngle, 10.0f), -10.0f);
			twist = gyroAngle / 30.0;
			printf("GYRO CORRECTION\n");
		}
	}

	printf("Xpos: %f  YPos:  %f  Twist: %f\n", xPos, yPos, twist);

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
	}
	else {
		STR = -STR;
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
	
//	SmartDashboard::PutNumber("wheelSpeedFR", wheelSpeedFR);
//	SmartDashboard::PutNumber("wheelSpeedFL", wheelSpeedFL);
//	SmartDashboard::PutNumber("wheelSpeedBR", wheelSpeedBR);
//	SmartDashboard::PutNumber("wheelSpeedBL", wheelSpeedBL);
//	SmartDashboard::PutNumber("wheelAngleFR", FRWheel->GetAngle());
//	SmartDashboard::PutNumber("wheelAngleFL", FLWheel->GetAngle());
//	SmartDashboard::PutNumber("wheelAngleBR", BRWheel->GetAngle());
//	SmartDashboard::PutNumber("wheelAngleBL", BLWheel->GetAngle());
	
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
	FLWheel->Set(wheelSpeedFL, wheelAngleFL + 180);
	FRWheel->Set(wheelSpeedFR, wheelAngleFR + 180);
	BRWheel->Set(wheelSpeedBR, wheelAngleBR + 180);
	BLWheel->Set(wheelSpeedBL, wheelAngleBL + 180);
	
//	FLWheel->Set(wheelSpeedFL, wheelAngleFL + 180);
//	FRWheel->Set(wheelSpeedFR, wheelAngleFR + 180);
//	BRWheel->Set(wheelSpeedBR, 0);
//	BLWheel->Set(wheelSpeedBL, wheelAngleBL + 180);
	
	angleOffset = wheelAngleFL + 180;
	
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
	FLWheel->GetController()->SetPID(p,FLWheel->GetController()->GetI(),FLWheel->GetController()->GetD());
	FRWheel->GetController()->SetPID(p,FRWheel->GetController()->GetI(),FRWheel->GetController()->GetD());
	BRWheel->GetController()->SetPID(p,BRWheel->GetController()->GetI(),BRWheel->GetController()->GetD());
	BLWheel->GetController()->SetPID(p,BLWheel->GetController()->GetI(),BLWheel->GetController()->GetD());
}

float DriveTrain::GetI() { 
	return FLWheel->GetController()->GetI();
}

void DriveTrain::SetI(float i) {
	FLWheel->GetController()->SetPID(FLWheel->GetController()->GetP(),i,FLWheel->GetController()->GetD());
	FRWheel->GetController()->SetPID(FRWheel->GetController()->GetP(),i,FRWheel->GetController()->GetD());
	BRWheel->GetController()->SetPID(BRWheel->GetController()->GetP(),i,BRWheel->GetController()->GetD());
	BLWheel->GetController()->SetPID(BLWheel->GetController()->GetP(),i,BLWheel->GetController()->GetD());
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
	printf("actual angle %f \n", BRWheel->GetAngle());
	printf("angle %f wheel %d \n", angle, wheel);
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
}
bool DriveTrain::IsGyroCorrection() const {
	return gyroCorrection;
}

IMU* DriveTrain::GetIMU()
{
	return imu;
}
