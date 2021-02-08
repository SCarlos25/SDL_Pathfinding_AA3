#pragma once
#include "STRIPS.h"

class ShootSTRIPS : public STRIPS {
public:
	float counter;
	float time_shooting;

	ShootSTRIPS();

	void Update(Agent* agent);

	void Init()
	{

	}

	void Exit()
	{

	}
};