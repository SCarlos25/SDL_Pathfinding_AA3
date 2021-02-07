#pragma once
class Enemy
{};

class DecisionMakingAlgorithm
{
public:
	Enemy *agentBase;

	virtual void Init(Enemy* gBase);

	virtual void Update();
};