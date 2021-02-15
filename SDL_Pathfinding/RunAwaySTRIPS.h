#pragma once
#include "STRIPS.h"

class RunAwaySTRIPS : public STRIPS {
public:
	std::stack<Node> path;
	Vector2D lastEnemyPos;
	float refreshDistance = 32;
	//float dist;

	RunAwaySTRIPS();

	void Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* _blackboard);

	void Init();

	/*void Exit()
	{

	}*/

	std::queue<STRIPS*> GetNeighbours();

	Vector2D GetFinalTarget(Vector2D target, const Vector2D& currPos, const Vector2D& margins);
};