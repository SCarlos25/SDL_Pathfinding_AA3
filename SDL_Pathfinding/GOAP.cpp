#include "GOAP.h"
#include "ExploreSTRIPS.h"

class Grid;

void GOAP::Init(Enemy* _allyAgent, Enemy* _enemyAgent, Grid* _maze)
{
	agentBase = _allyAgent;
	enemyAgent = _enemyAgent;
	maze = _maze;
	currBehaviour = new ExploreSTRIPS(true);
}

void GOAP::Update()
{
	currBehaviour->Update(agentBase, enemyAgent, maze);
}

void GOAP::ChangeStrips(STRIPS* change)
{
	currBehaviour->Exit();
	currBehaviour = change;
	currBehaviour->Init();
}
