#pragma once
#include "STRIPS.h"

class ReloadWeaponSTRIPS : public STRIPS {
public:
	float reloadingDelay = 2.0f;
	float currTime = 0;

	ReloadWeaponSTRIPS();

	void Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* _blackboard);

	void Init();

	/*void Exit()
	{
		while (!neighbours.empty()) {
			delete[] neighbours.front();
			neighbours.pop();
		}
	}*/

	std::queue<STRIPS*> GetNeighbours();
};