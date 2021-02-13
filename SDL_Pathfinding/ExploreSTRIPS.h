#pragma once
#include "STRIPS.h"

class ExploreSTRIPS : public STRIPS {
public:
	bool arrived;
	std::stack<Node> path;

	ExploreSTRIPS(bool initNeighbours);

	//No necessitem enemy, pero fem servir la mateixa per comoditat i prq al passar un punter no te gaire impacte en l'eficiencia
	void Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* _blackboard);

	void Init()
	{

	}

	/*void Exit()
	{

	}*/
};
