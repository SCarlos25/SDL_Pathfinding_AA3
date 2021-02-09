#include "FiniteStateMachine.h"

void FiniteStateMachine::Init(Agent *gBase)
{
	agentBase = gBase;
	currBehaviour = new WanderBehaviour(this);
}

void FiniteStateMachine::Update(Enemy *enemyAgent, Grid *maze)
{
	currBehaviour->Update();
}