#pragma once
#include "STRIPS.h"

class AimSTRIPS : public STRIPS {
public:

	float aimingDelay = 1.0f;
	float currTime = 0;
	//clock_t initTime;
	//clock_t goalTime;

	AimSTRIPS(bool initNeighbours);

	void Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* _blackboard);

	void Init();

	//void Exit()
	//{
	//	// Por si hay que modificar el valor de una variable
	//}

	std::queue<STRIPS*> GetNeighbours();
};