#include "GOAP.h"

#include "ExploreSTRIPS.h"
#include "ApproachSTRIPS.h"

#include "Enemy.h"

#include "Priority_STRIPS.h"

class Grid;

void GOAP::Init(Enemy* _allyAgent, Enemy* _enemyAgent, Grid* _maze, Blackboard* _blackboard)
{
	agentBase = _allyAgent;
	enemyAgent = _enemyAgent;
	maze = _maze;
	blackboard = _blackboard;
	currBehaviour = new ExploreSTRIPS(true);
	/*if (*currBehaviour != behaviours.front()) {
		
	}*/

	std::stack<STRIPS*> behaviorsStack = GOAP_AStar(currBehaviour, "enemyAlive", false);
	//behaviorsStack.push()
	while (!behaviorsStack.empty()) {
		behaviours.push(behaviorsStack.top());
		behaviorsStack.pop();
	}

	currBehaviour->Init();

	//printf("Current Type: %d /n", currBehaviour->type);
	std::cout << "Behaviour " << (int)currBehaviour->type << std::endl;
}

void GOAP::Update()
{
	currBehaviour->Update(agentBase, enemyAgent, maze, blackboard);
}

void GOAP::ChangeStrips(/*STRIPS* change*/)
{
	currBehaviour->Exit();
	if (!behaviours.empty()) {
		currBehaviour = behaviours.front();
		//*currBehaviour = *behaviours.front();
		//currBehaviour = &behaviours.front();
		//delete[] currBehaviour;
		behaviours.pop();
	}

	if (currBehaviour->type != STRIPS::STRIPSTypes::SHOOT && currBehaviour->type != STRIPS::STRIPSTypes::DETONATE) {
		if ((behaviours.empty() || !currBehaviour->ConditionsAccomplished(blackboard->conditions))
			&& (blackboard->conditions["enemyAlive"] == true || blackboard->conditions["agentAlive"] == false))
		{
			behaviours = std::queue<STRIPS*>();
			std::stack<STRIPS*> behaviorsStack = GOAP_AStar(currBehaviour, "enemyAlive", false);

			while (!behaviorsStack.empty()) {
				behaviours.push(behaviorsStack.top());
				behaviorsStack.pop();
			}

			currBehaviour = behaviours.front();
			behaviours.pop();
		}
	}
	agentBase->clearPath();

	currBehaviour->Init();

	std::cout << "Behaviour " << (int)currBehaviour->type << std::endl;
}

std::stack<STRIPS*> GOAP::GOAP_AStar(STRIPS* start, std::string targetKey, bool targetState) // targetState = !enemyAlive
{

	if (blackboard->conditions[targetKey] == targetState)
	{
		std::stack<STRIPS*> path;
		path.push(start);
		return path;
	}

	std::priority_queue<Priority_STRIPS> frontier;
	frontier.push(Priority_STRIPS(start, 0));

	std::unordered_map<STRIPS, STRIPS*> came_from;
	came_from[*start] = new STRIPS();

	std::unordered_map<STRIPS, float> cost_so_far;
	cost_so_far[*start] = 0;

	std::unordered_map<STRIPS, std::unordered_map<std::string, bool>> conditionsMap;
	conditionsMap[*start] = blackboard->conditions;

	STRIPS* current = new STRIPS;
	current = start;
	bool targetAccomplished = false;
	//current->cameFrom = nullptr;
	//current->costSoFar = 0;

	while (!frontier.empty())
	{
		//current = new STRIPS;
		current = frontier.top().strips;
		frontier.pop();
		std::unordered_map<std::string, bool> currConditions = conditionsMap[*current];
		if (currConditions[targetKey] == targetState)
		{
			targetAccomplished = true;
			break;
		}

		std::queue<STRIPS*> neighbors = current->GetNeighbours();
		while (!neighbors.empty())
		{
			STRIPS* next = new STRIPS;
			next = neighbors.front();
			neighbors.pop();

			float new_cost = cost_so_far[*current] + next->cost;

			if ((/*cost_so_far[*next] < 0*/ /*cost_so_far.find(*next) == cost_so_far.end()*/ /*|| new_cost < cost_so_far[*next]) &&*/ next->ConditionsAccomplished(currConditions)))
			{
				cost_so_far[*next] = new_cost;
				float priority = new_cost;
				frontier.push(Priority_STRIPS(next, priority));
				came_from[*next] = current;
				//conditionsMap[next] = next.GetNewConditions(conditionsMap[current]);
				conditionsMap[*next] = currConditions;
				next->TriggerEffects(conditionsMap[*next]);
			}
		}
	}
	std::stack<STRIPS*> path;
	
	if (!targetAccomplished)
	{
		//std::cout << "No path found!" << std::endl;

		blackboard->PrintConditions();

		path.push(new ExploreSTRIPS(true)); //current
	}
	else
	{
		//Target found, reconstruct path that we took!
		STRIPS* temp = new STRIPS();
		temp = current;
		path.push(temp);
		while (came_from[*temp] != start)
		{
			path.push(came_from[*temp]);
			temp = came_from[*temp];
		}
		//path.push(*start);
	}
	
	return path;
}

