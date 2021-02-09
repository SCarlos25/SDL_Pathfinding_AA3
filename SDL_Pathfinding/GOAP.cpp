#include "GOAP.h"
#include "ExploreSTRIPS.h"

class Grid;

void GOAP::Init(Ally* gBase)
{
	agentBase = gBase;
	currBehaviour = new ExploreSTRIPS();
}

void GOAP::Update(Enemy *enemyAgent, Grid *maze)
{
	currBehaviour->Update(agentBase, enemyAgent, maze);
}



