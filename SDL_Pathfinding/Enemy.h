#pragma once
#include "../src/Agent.h"
#include "FiniteStateMachine.h"


class Enemy : public Agent
{
public:
	DecisionMakingAlgorithm* currAlgorithm;

	Enemy();

	void Init(Vector2D pos);

	void SetFiniteStateMachine();

	void Update();

};