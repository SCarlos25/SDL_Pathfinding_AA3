#pragma once
class Enemy;
class Grid;

class DecisionMakingAlgorithm
{
public:
	Enemy* agentBase;
	Enemy* enemyAgent;
	Grid* maze;

	virtual void Init(Enemy* _allyAgent, Enemy* _enemyAgent, Grid* maze) {}

	virtual void Update() {}
};