#pragma once
#include "STRIPS.h"

class RunAwaySTRIPS : public STRIPS {
public:
	std::stack<Node> path;
	Vector2D lastEnemyPos;
	float refreshDistance = 999;
	//float dist;

	RunAwaySTRIPS(bool initNeighbours);

	void Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* _blackboard);

	void Init()
	{
		lastEnemyPos = Vector2D(-1, -1);
	}

	/*void Exit()
	{

	}*/

	std::queue<STRIPS*> GetNeighbours();

	Vector2D GetFinalTarget(Vector2D target, const Vector2D& currPos, const Vector2D& margins);
};