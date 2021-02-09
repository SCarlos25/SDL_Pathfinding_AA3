#pragma once
class Enemy;
class Ally;

class DecisionMakingAlgorithm
{
public:
	virtual void Init(Enemy* gBase);

	virtual void Update();
};