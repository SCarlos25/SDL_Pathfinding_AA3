#pragma once
#include "STRIPS.h"

class RunAwaySTRIPS : public STRIPS {
public:
	std::stack<Node> path;

	RunAwaySTRIPS(bool initNeighbours);

	void Update(Enemy* agent, Enemy* enemy, Grid* maze);

	void Init()
	{

	}

	void Exit()
	{

	}
};