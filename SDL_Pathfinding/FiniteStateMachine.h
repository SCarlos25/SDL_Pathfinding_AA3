#pragma once
#include "DecisionMakingAlgorithm.h"
#include "BaseBehaviour.h"
#include "Wander_Behaviour.h"
#include "Flee_Behaviour.h"
#include "Chase_Behaviour.h"

class FiniteStateMachine: DecisionMakingAlgorithm
{
	BaseBehaviour *currBehaviour;
public:


	void Init(Enemy *gBase);

	void Update();

};