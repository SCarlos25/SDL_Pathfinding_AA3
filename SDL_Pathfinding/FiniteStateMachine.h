#pragma once
#include "DecisionMakingAlgorithm.h"
#include "BaseBehaviour.h"
#include "Wander_Behaviour.h"

class Enemy;

class FiniteStateMachine: public DecisionMakingAlgorithm
{
public:
	BaseBehaviour *currBehaviour;

	void Init(Enemy *gBase, Enemy *enemy, Grid *maze) override;

	void Update() override;

};