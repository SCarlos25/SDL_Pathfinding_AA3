#pragma once
#include "STRIPS.h"

class AimSTRIPS : public STRIPS {
public:

	float counter;
	float time_aiming;

	AimSTRIPS();

	void Update(Agent* agent);

	void Init()
	{
		// time to exit = Time.time + time_aiming
	}

	void Exit()
	{
		// Por si hay que modificar el valor de una variable
	}
};