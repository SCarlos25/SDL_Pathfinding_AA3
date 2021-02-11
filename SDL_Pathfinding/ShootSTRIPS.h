#pragma once
#include "STRIPS.h"

class ShootSTRIPS : public STRIPS {
public:
	float counter;
	float time_shooting;

	ShootSTRIPS(bool initNeighbours);

	void Update(Enemy* agent, Enemy* enemy, Grid* maze);

	void Init()
	{

	}

	void Exit()
	{

	}
};