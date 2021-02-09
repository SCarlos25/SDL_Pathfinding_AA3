#include "FiniteStateMachine.h"

void FiniteStateMachine::Init(Agent *gBase)
{
	agentBase = gBase;
	currBehaviour = new WanderBehaviour(this);
}

void FiniteStateMachine::Update()
{
	currBehaviour->Update();
}