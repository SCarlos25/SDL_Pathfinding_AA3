#include "FiniteStateMachine.h"

void FiniteStateMachine::Init(Enemy *_allyAgent, Enemy *_enemyAgent, Grid * _maze)
{
	agentBase = _allyAgent;
	enemyAgent = _enemyAgent;
	maze = _maze;
	currBehaviour = new WanderBehaviour(this);
}

void FiniteStateMachine::Update()
{
	currBehaviour->Update();
}