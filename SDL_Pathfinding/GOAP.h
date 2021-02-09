#pragma once
#include "DecisionMakingAlgorithm.h"
#include "Blackboard.h"

class GOAP : DecisionMakingAlgorithm {
public:
	Ally* agentBase;
	STRIPS* currBehaviour;

	//Blackboard* blackboard;

	void Init(Ally* gBase);

	void Update(Enemy* enemyAgent, Grid* maze);

};