#pragma once
#include "../src/Agent.h"
#include "FiniteStateMachine.h"


class Enemy : public Agent
{
public:
	DecisionMakingAlgorithm* currAlgorithm;

	Enemy() {};
	void SetFiniteStateMachine();

	void Update();

};