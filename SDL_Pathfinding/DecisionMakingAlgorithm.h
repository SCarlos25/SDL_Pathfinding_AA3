#pragma once
class Enemy;
class Grid;
class STRIPS;

class DecisionMakingAlgorithm
{
public:
	Enemy* agentBase;
	Enemy* enemyAgent;
	Grid* maze;

	virtual void Init(Enemy* _allyAgent, Enemy* _enemyAgent, Grid* maze) { return; }

	virtual void Update() { return; }

	virtual void ChangeStrips(STRIPS* change) {};

};