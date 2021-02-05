#pragma once
#include "DecisionMakingAlgorithm.h"
#include "BaseBehaviour.h"

class FiniteStateMachine: DecisionMakingAlgorithm
{
	BaseBehaviour *currBehaviour;

	void Update(Enemy *enemy);



};