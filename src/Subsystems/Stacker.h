#ifndef Stacker_H
#define Stacker_H

#include "Commands/Subsystem.h"
#include "WPILib.h"
#include "../Components/Lift2481.h"


class Stacker: public Subsystem
{
private:
	// It's desirable that everything possible under private except
	// for methods that implement subsystem capabilities
	Lift2481* mRightLift;
	int mToteCount, mDesiredToteCount;

public:
	enum StackerLiftID{
			RIGHT,
			LEFT,
		};

	Stacker();
	void InitDefaultCommand();
	void Reset();
	bool OnTarget();
	void SetPosition(float, bool loaded = false);
	void PeriodicUpdate();
	void Disable(bool motor = true, bool brake = true);
	void Enable(bool motor = true);
	bool IsResetting();
	bool IsEnabled();
	int GetToteCount() const;
	void ResetToteCount();
	void SetToteCount(int toteCount);
	void IncrementToteCount();
	void DecrementToteCount();
	void Set(float output);
	float GetPosition();
	void StackerManual(float yValue);
	int getDesiredToteCount() const;
	void setDesiredToteCount(int desiredToteCount);
};

#endif
