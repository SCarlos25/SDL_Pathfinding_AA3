#pragma once
#include "DecisionMakingAlgorithm.h"
#include "Blackboard.h"

class GOAP : DecisionMakingAlgorithm {
public:
	STRIPS* currBehaviour;

	//Blackboard* blackboard;

	void Init(Enemy* _allyAgent, Enemy* _enemyAgent, Grid* _maze);

	void Update();

	void ChangeStrips(STRIPS* change);

};
