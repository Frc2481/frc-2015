
#include <cmath>
#include "SwerveModule.h"
#include "PController.h"


SwerveModule::SwerveModule(uint32_t driveChannel, uint32_t steerChannel, uint32_t steerEncoder) : 
				mDrive(new CANTalon(driveChannel)),
				mSteer(new CANTalon(steerChannel)),
				mEncoder(new ContinuousEncoder(steerEncoder)),
				mSteerController(new PController(mEncoder, mSteer, 0.015, 0)),
				prevAngle(0),
				optimized(true)
{

	mSteerController->SetInputRange(0, 360);
	mSteerController->SetTolerance(1);
	mSteerController->SetContinuous(true);
	mSteer->ConfigNeutralMode(CANTalon::kNeutralMode_Coast);
}

SwerveModule::~SwerveModule(){
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
	while(angle > 360.0f)
		angle -= 360.0f;
	while(angle < 0.0f)
		angle += 360.0f;

	float currentAngle = GetAngle();

//	if (optimized){
		if (fabs(angle - currentAngle) > 90 && fabs(angle - currentAngle) < 270) {
			angle = ((int)angle + 180) % 360;
			speed = -speed;
		}

		//If we are moving slowly, don't change the angle to keep things stable (rotating wheels when speed is small can induce lateral movement)
		if (fabs(speed) < .05){
			angle = prevAngle;
		}
		else {
			prevAngle = angle;
		}
//	}
//	else {
//		speed *= 0.2;
//	}

	mDrive->Set(speed);
	mSteerController->SetSetpoint(angle);
}

float SwerveModule::GetOffset() const{
    return mEncoder->GetOffset();
}

void SwerveModule::SetOffset(float offset){
    mEncoder->SetOffset(offset);
}

PController* SwerveModule::GetController() {
	return mSteerController;
}
void SwerveModule::SetOptimized(bool isOptimized){
	optimized = isOptimized;
}

float SwerveModule::GetVoltage() {
	return mEncoder->getVoltage();
}

float SwerveModule::GetRawVoltage() {
	return mEncoder->GetRawVoltage();
}

void SwerveModule::SetBrake(bool brake) {
	mDrive->ConfigNeutralMode(brake ? CANTalon::kNeutralMode_Brake : CANTalon::kNeutralMode_Coast);
}
