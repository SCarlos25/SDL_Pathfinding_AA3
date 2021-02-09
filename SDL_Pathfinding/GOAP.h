#pragma once
#include "DecisionMakingAlgorithm.h"
#include "Blackboard.h"

class GOAP : DecisionMakingAlgorithm {
public:
	Enemy* agentBase;
	STRIPS* currBehaviour;

	//Blackboard* blackboard;

	void Init(Enemy* gBase) override;

	void Update(Enemy* enemyAgent, Grid* maze) override;

};