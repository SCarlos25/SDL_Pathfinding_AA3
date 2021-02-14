#pragma once
#include "STRIPS.h"

class ApproachEnemySTRIPS : public STRIPS {
public:
	std::stack<Node> path;
	Vector2D lastEnemyPos;
	float refreshDistance = 999;

	ApproachEnemySTRIPS(bool initNeighbours);

	void Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* _blackboard);

	void Init()
	{
		lastEnemyPos = Vector2D(-1, -1);
	}

	/*void Exit()
	{

	}*/

	std::queue<STRIPS*> GetNeighbours();
};