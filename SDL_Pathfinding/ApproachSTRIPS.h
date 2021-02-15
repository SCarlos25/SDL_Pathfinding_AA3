#pragma once
#include "STRIPS.h"

class ApproachEnemySTRIPS : public STRIPS {
public:
	std::stack<Node> path;
	Vector2D lastEnemyPos;
	float refreshDistance = 32;

	ApproachEnemySTRIPS(bool initNeighbours);

	void Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* _blackboard);

	void Init();

	/*void Exit()
	{

	}*/

	std::queue<STRIPS*> GetNeighbours();
};