#pragma once
#include "../src/Agent.h"
#include "FiniteStateMachine.h"

class Enemy : public Agent // Agente aqui da error
{
public:

	bool hasGun;

	DecisionMakingAlgorithm* currAlgorithm;

	Enemy* targetEnemy;

	Enemy() { hasGun = false; return; }

	void Init(Vector2D pos);

	void SetTargetEnemy(Enemy *gTargetEnemy);

	void SetFiniteStateMachine();

	void SetGOAP() { return; }

	void UpdateEnemy();

	void GiveGun();

	void TakeGun();

};