#pragma once
#include "STRIPS.h"

class ExploreSTRIPS : public STRIPS {
public:
	bool arrived;
	std::stack<Node> path;

	ExploreSTRIPS();

	void Update(Agent* agent, Grid* maze);

	void Init()
	{

	}

	void Exit()
	{

	}
};
