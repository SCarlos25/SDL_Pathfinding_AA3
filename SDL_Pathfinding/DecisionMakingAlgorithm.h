#pragma once
class Enemy;
class Grid;

class DecisionMakingAlgorithm
{
public:
	virtual void Init(Enemy* gBase);

	virtual void Update(Enemy* enemyAgent, Grid* maze);
};