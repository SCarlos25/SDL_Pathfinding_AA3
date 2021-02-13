#include "FiniteStateMachine.h"
#include "Blackboard.h"

void FiniteStateMachine::Init(Enemy *_allyAgent, Enemy *_enemyAgent, Grid * _maze, Blackboard* _blackboard)
{
	agentBase = _allyAgent;
	enemyAgent = _enemyAgent;
	maze = _maze;
	blackboard = _blackboard;
	currBehaviour = new WanderBehaviour(this);
}

void FiniteStateMachine::Update()
{
	currBehaviour->Update();
}