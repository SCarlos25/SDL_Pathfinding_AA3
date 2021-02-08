#pragma once
#include "STRIPS.h"

class RunAwaySTRIPS : public STRIPS {
public:
	std::stack<Node> path;

	RunAwaySTRIPS();

	void Update(Agent* agent, Grid* maze);

	void Init()
	{

	}

	void Exit()
	{

	}
};