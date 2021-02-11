#pragma once
#include "STRIPS.h"

class ReloadWeaponSTRIPS : public STRIPS {
public:
	float counter;
	float time_reloading;

	ReloadWeaponSTRIPS(bool initNeighbours);

	void Update(Enemy* agent, Enemy* enemy, Grid* maze);

	void Init()
	{

	}

	void Exit()
	{

	}
};