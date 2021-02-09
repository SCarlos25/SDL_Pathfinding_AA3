#include "GOAP.h"
#include "ExploreSTRIPS.h"

void GOAP::Init(Enemy* gBase)
{
	agentBase = gBase;
	currBehaviour = new ExploreSTRIPS();
}

void GOAP::Update(Enemy *enemyAgent, Grid *maze)
{
	currBehaviour->Update(agentBase, enemyAgent, maze);
}



