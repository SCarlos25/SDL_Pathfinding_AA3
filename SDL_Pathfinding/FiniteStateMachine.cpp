#include "FiniteStateMachine.h"

void FiniteStateMachine::Init(Enemy *gBase)
{
	agentBase = gBase;
	currBehaviour = new WanderBehaviour(this);
}

void FiniteStateMachine::Update()
{
	//currBehaviour->Update();
}