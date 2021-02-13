#pragma once
#include "STRIPS.h"

class DetonateBombSTRIPS : public STRIPS {
public:
	float counter;
	float time_detonating;

	DetonateBombSTRIPS(bool initNeighbours);

	void Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* _blackboard);

	void Init()
	{

	}

	/*void Exit()
	{

	}*/
};
