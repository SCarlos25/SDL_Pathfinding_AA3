#pragma once
#include "../src/Agent.h"
#include "FiniteStateMachine.h"


class Enemy : public Agent // Agente aqui da error
{
public:
	DecisionMakingAlgorithm* currAlgorithm;

	Enemy* targetEnemy;

	Enemy() { return; }

	void Init(Vector2D pos);

	void SetTargetEnemy(Enemy *gTargetEnemy);

	void SetFiniteStateMachine();

	void SetGOAP() { return; }

	void UpdateEnemy();

};