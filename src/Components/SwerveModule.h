#ifndef SWERVEMODULE_H_
#define SWERVEMODULE_H_
#include <WPILib.h>
#include "ContinuousEncoder.h"


class SwerveModule {
private:
    CANTalon *mDrive;
    CANTalon *mSteer;
    ContinuousEncoder *mEncoder;
    PIDController *mSteerController;
    float prevAngle;
    float offset;
    bool optimized;
    
	
public:
	SwerveModule(uint32_t driveChannel, uint32_t steerChannel, uint32_t steerEncoder);
	virtual ~SwerveModule();
	void Set(float speed, float angle);
	float GetSpeed()const;
	float GetAngle()const;
	float GetRawAngle()const;
	float GetOffset() const;
	void SetOffset(float offset);
	float DegToVolts(float deg);
	PIDController* GetController();
	void SetOptimized(bool isOptimized);
};

#endif /*SWERVEMODULE_H_*/
