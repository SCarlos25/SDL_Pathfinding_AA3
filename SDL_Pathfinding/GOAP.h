#pragma once
#include "DecisionMakingAlgorithm.h"
#include "Blackboard.h"

class GOAP : DecisionMakingAlgorithm {
public:
	STRIPS* currBehaviour;
	std::queue<STRIPS> behaviours;

	//Blackboard* blackboard;

	void Init(Enemy* _allyAgent, Enemy* _enemyAgent, Grid* _maze) override;

	void Update() override;

	void ChangeStrips(STRIPS* change);

};
