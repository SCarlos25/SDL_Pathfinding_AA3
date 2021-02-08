#pragma once
//class Enemy;

class DecisionMakingAlgorithm
{
public:
	virtual void Init(Enemy* gBase);

	virtual void Update();
};