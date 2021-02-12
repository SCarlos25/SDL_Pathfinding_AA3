#pragma once
#include "STRIPS.h"

class AimSTRIPS : public STRIPS {
public:

	//float counter;
	float aimingTime = 1.0f;
	//clock_t initTime;
	//clock_t goalTime;

	AimSTRIPS(bool initNeighbours);

	void Update(Enemy* agent, Enemy* enemy, Grid* maze);

	void Init();

	//void Exit()
	//{
	//	// Por si hay que modificar el valor de una variable
	//}
};