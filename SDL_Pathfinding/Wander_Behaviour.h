#pragma once
#include "BaseBehaviour.h"

class WanderBehaviour : public BaseBehaviour
{
private:
	//Time vars
	float futWanderTime = 0;
	int minWanderDelay = 2;
	int maxWanderDelay = 3.5;
	float currTime = 0;

	//Wander position vars
	float maxWanderRange = 260;
	float minWanderRange = 140;

	//Visual check distance


public:
	WanderBehaviour(FiniteStateMachine *gMachine)
	{
		machineState = gMachine;
	}
	
	void Init() override;
	
	void Update() override;
	
	void Exit() override;
};
