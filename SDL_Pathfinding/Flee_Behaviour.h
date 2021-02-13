#pragma once
#include "BaseBehaviour.h"

class FleeBehaviour : public BaseBehaviour
{
public:
	FleeBehaviour(FiniteStateMachine* gMachine)
	{
		machineState = gMachine;
	}

	void Init() override;

	void Update() override;

	void Exit() override;
};