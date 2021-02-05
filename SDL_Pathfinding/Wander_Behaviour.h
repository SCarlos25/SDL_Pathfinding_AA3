#pragma once
#include "BaseBehaviour.h"

class WanderBehaviour : public BaseBehaviour
{
public:
	WanderBehaviour(FiniteStateMachine *gMachine)
	{
		machineState = gMachine;
	}
	
	void Init();
	
	void Update() override;
	
	void Exit();
};
