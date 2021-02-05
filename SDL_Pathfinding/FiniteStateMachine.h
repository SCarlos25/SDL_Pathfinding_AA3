#pragma once
#include "DecisionMakingAlgorithm.h"
#include "BaseBehaviour.h"
#include "Wander_Behaviour.h"

class FiniteStateMachine: DecisionMakingAlgorithm
{
public:
	Enemy *agentBase;
	BaseBehaviour *currBehaviour;

	void Init(Enemy *gBase);

	void Update();

};