
#include <cmath>
#include "SwerveModule.h"
//#include "PController.h"


SwerveModule::SwerveModule(uint32_t driveChannel, uint32_t steerChannel, uint32_t steerEncoder) : 
				mDrive(new CANTalon(driveChannel)),
				mSteer(new CANTalon(steerChannel)),
				mEncoder(new ContinuousEncoder(steerEncoder)),
				mSteerController(new PIDController(.035, 0, 0, mEncoder, mSteer)),
				prevAngle(0),
				optimized(true)
{
//	mDrive->SetSafetyEnabled(true);
//	mSteer->SetSafetyEnabled(true);
//	mSteerController->SetOutputRange(-1,1);

	mSteerController->SetInputRange(0, 360);
	mSteerController->SetTolerance(4);
//	mSteerController->SetInputRange(0.015, 4.987);
//	mSteerController->SetInputRange(0, 360);
//	mSteerController->SetAbsoluteTolerance(2);
//	mSteerController->SetContinuous(true);
//	mSteerController->Enable();
//	mSteerController->
	
}

SwerveModule::~SwerveModule()
{
	delete mDrive;
	delete mSteer;
	delete mEncoder;
	delete mSteerController;
}
float SwerveModule::GetAngle()const{
	return mEncoder->GetAngle();
}

float SwerveModule::GetRawAngle()const{
	return mEncoder->GetRawAngle();
}

float SwerveModule::GetSpeed()const{
	return mDrive->Get();
}

float SwerveModule::DegToVolts(float deg) {
	return (deg + 180) / 80 + 0.25;
}

void SwerveModule::Set(float speed, float angle){
	float currentAngle = GetAngle();
	/*
	if (fabs(angle - currentAngle) > 90 && fabs(angle - currentAngle) < 270){
		angle = ((int)angle + 180) % 360;
		speed = -speed;
		//printf("reverse");
	}
	*/
	if (optimized){
		if (fabs(angle - currentAngle) < 90 || fabs(angle - currentAngle) > 270) {
			
		}
		else {
			angle = ((int)angle + 180) % 360;
			speed = -speed;
		}
		if (fabs(speed) < .1){
			angle = prevAngle;
		}
		else {
			prevAngle = angle;
		}
	}
	else {
		speed *= 0.2;
	}
	//printf("angle = %f \n", GetAngle());
	//SmartDashboard::PutNumber("Angle", GetAngle());
	mDrive->Set(speed);
	mSteerController->SetSetpoint(angle);
}

float SwerveModule::GetOffset() const
{
    return mEncoder->GetOffset();
}

void SwerveModule::SetOffset(float offset)
{
    mEncoder->SetOffset(offset);
    mSteerController->SetSetpoint(0);
}

PIDController* SwerveModule::GetController() {
	return mSteerController;
}
void SwerveModule::SetOptimized(bool isOptimized){
	optimized = isOptimized;
}
