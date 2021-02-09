#pragma once
#include "STRIPS.h"

class ApproachEnemySTRIPS : public STRIPS {
public:
	std::stack<Node> path;

	ApproachEnemySTRIPS();

	void Update(Enemy* agent, Enemy* enemy, Grid* maze);

	void Init()
	{

	}

	void Exit()
	{

	}
};