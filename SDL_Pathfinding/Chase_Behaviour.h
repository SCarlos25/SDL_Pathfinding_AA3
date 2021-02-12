#pragma once
#include "BaseBehaviour.h"

class ChaseBehaviour : public BaseBehaviour
{
public:
	ChaseBehaviour(FiniteStateMachine* gMachine)
	{
		machineState = gMachine;
	}

	void Init() override;

	void Update() override;

	void Exit() override;
};