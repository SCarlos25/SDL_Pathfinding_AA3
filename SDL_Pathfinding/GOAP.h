#pragma once
#include "DecisionMakingAlgorithm.h"
#include "Blackboard.h"
#include "STRIPS.h"

class GOAP : public DecisionMakingAlgorithm {
public:
	STRIPS* currBehaviour;
	std::queue<STRIPS*> behaviours;

	Blackboard* blackboard;

	GOAP() {}

	void Init(Enemy* _allyAgent, Enemy* _enemyAgent, Grid* _maze, Blackboard* _blackboard) override;

	void Update() override;

	void ChangeStrips(/*STRIPS* change*/);

	std::stack<STRIPS*> GOAP_AStar(STRIPS* start, std::string targetKey, bool targetState);

};
