#pragma once
#include "BaseBehaviour.h"

class WanderBehaviour : public BaseBehaviour
{
public:
	WanderBehaviour(FiniteStateMachine *gMachine)
	{
		machineState = gMachine;
	}
	
	void Init() override;
	
	void Update() override;
	
	void Exit() override;
};
