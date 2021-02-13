#pragma once
#include "STRIPS.h"

class ShootSTRIPS : public STRIPS {
public:
	float counter;
	float time_shooting;

	ShootSTRIPS(bool initNeighbours);

	void Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* _blackboard);

	void Init()
	{

	}

	/*void Exit()
	{

	}*/
};