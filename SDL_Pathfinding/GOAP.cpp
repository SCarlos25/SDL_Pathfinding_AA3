#include "GOAP.h"
#include "ExploreSTRIPS.h"

class Grid;

void GOAP::Init(Enemy* _allyAgent, Enemy* _enemyAgent, Grid* _maze)
{
	agentBase = _allyAgent;
	enemyAgent = _enemyAgent;
	maze = _maze;
	currBehaviour = new ExploreSTRIPS(true);
	/*if (*currBehaviour != behaviours.front()) {
		std::stack<STRIPS> behaviorsStack = Blackboard::GetInstance()->GOAP_AStar(currBehaviour, "enemyAlive", false);
		while (!behaviorsStack.empty()) {
			behaviours.push(behaviorsStack.top());
			behaviorsStack.pop();
		}
	}*/
	currBehaviour->Init();

	printf("Current Type: %d /n", currBehaviour->type);
}

void GOAP::Update()
{
	currBehaviour->Update(agentBase, enemyAgent, maze);
}

void GOAP::ChangeStrips(STRIPS* change)
{
	currBehaviour->Exit();
	delete[] currBehaviour;
	behaviours.pop();
	/*if (*change != behaviours.front()) {
		std::stack<STRIPS> behaviorsStack = Blackboard::GetInstance()->GOAP_AStar(change, "enemyAlive", false);
		while (!behaviorsStack.empty()) {
			behaviours.push(behaviorsStack.top());
			behaviorsStack.pop();
		}
	}*/
	currBehaviour = change;
	currBehaviour->Init();

	printf("Current Type: %d /n", currBehaviour->type);
}
