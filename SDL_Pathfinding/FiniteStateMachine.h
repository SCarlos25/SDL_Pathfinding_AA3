#pragma once
#include "DecisionMakingAlgorithm.h"
#include "BaseBehaviour.h"
#include "Wander_Behaviour.h"
#include "Enemy.h"

class FiniteStateMachine: DecisionMakingAlgorithm
{
public:
	Enemy *agentBase;
	BaseBehaviour *currBehaviour;

	void Init(Enemy *gBase) override;

	void Update() override;

};