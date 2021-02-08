#pragma once
#include "STRIPS.h"

class DetonateBombSTRIPS : public STRIPS {
public:
	float counter;
	float time_detonating;

	DetonateBombSTRIPS();

	void Update(Agent* agent);

	void Init()
	{

	}

	void Exit()
	{

	}
};
