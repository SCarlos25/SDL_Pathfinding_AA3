#pragma once
#include "../src/Agent.h"
#include "DecisionMakingAlgorithm.h"
#include "FiniteStateMachine.h"
#include "GOAP.h"


class Enemy : public Agent // Agente aqui da error
{
public:
	DecisionMakingAlgorithm* currAlgorithm;

	Enemy* targetEnemy;

	float seeRange = 100;

	Enemy() { return; }

	void Init(Vector2D pos);

	void SetTargetEnemy(Enemy *gTargetEnemy);

	void SetFiniteStateMachine(Blackboard* blackboard);
	void SetGOAP(Blackboard* blackboard);

	void SetGOAP() { return; }

	void UpdateEnemy();

};