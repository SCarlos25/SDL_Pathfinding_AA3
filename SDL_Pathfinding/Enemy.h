#pragma once
#include "../src/Agent.h"
#include "FiniteStateMachine.h"


class Enemy : public Agent // Agente aqui da error
{
public:
	DecisionMakingAlgorithm* currAlgorithm;

	Enemy();

	void Init(Vector2D pos);

	void SetFiniteStateMachine();

	void SetGOAP();

	void UpdateEnemy();

};