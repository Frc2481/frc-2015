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
	int mToteCount;
	float mMaxPower;
	PowerDistributionPanel p;

	enum Direction{
		Raising,
		Lowering
	} mCounterState;

	enum Stopped{
		Up,
		Down
	} mLiftLastExtreme;

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
	int GetToteCount() const;
	void ResetToteCount();
	void UpdateToteCount();
	void SetToteCount(int toteCount);
	void IncrementToteCount();
	void DecrementToteCount();
	void Set(float output);
	float GetPosition();
	void StackerManual(float yValue);
};

#endif
