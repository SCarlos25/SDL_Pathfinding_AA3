#pragma once
#include "STRIPS.h"

class ReloadWeaponSTRIPS : public STRIPS {
public:
	float counter;
	float time_reloading;

	ReloadWeaponSTRIPS();

	void Update(Agent* agent);

	void Init()
	{

	}

	void Exit()
	{

	}
};