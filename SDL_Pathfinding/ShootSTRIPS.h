#pragma once
#include "STRIPS.h"

class ShootSTRIPS : public STRIPS {
public:
	float shootingDelay = 0.5f;
	float currTime = 0;

	ShootSTRIPS(bool initNeighbours);

	void Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* _blackboard);

	void Init();

	/*void Exit()
	{

	}*/

	std::queue<STRIPS*> GetNeighbours();
};