#include "Blackboard.h"
#include "Priority_STRIPS.h"
#include "Enemy.h"
#include "Ally.h"

void Blackboard::UpdateConditionsState(Enemy* ally, Enemy* enemy)
{
	//conditions["agentAlive"] = ally->alive;
	//conditions["hasWeapon"] = ally->hasWeapon;
	//conditions["loadedWeapon"] = ally->loadedWeapon;
	//conditions["hasBomb"] = ally->hasBomb;
	//
	//conditions["enemyVisible"] = 
	//conditions["enemyNearby"] = Vector2D::DistanceSquared(ally->getPosition(), enemy->getPosition()) < AGENT_RANGE;
	//conditions["enemyAlive"] = enemy->alive;
	//conditions["enemyHasWeapon"] = enemy->hasWeapon;
	//conditions["enemyHasBomb"] = enemy->hasBomb;
}

// TODO: 
std::stack<STRIPS> Blackboard::GOAP_AStar(STRIPS* start, std::string targetKey, bool targetState) // targetState = !enemyAlive
{
	//if (conditions[targetKey] == targetState)
	//{
	//	std::stack<STRIPS> path;
	//	path.push(*start);
	//	return path;
	//}
	//
	//std::priority_queue<Priority_STRIPS> frontier;
	//frontier.push(Priority_STRIPS(*start, 0));
	//
	//std::unordered_map<STRIPS, STRIPS> came_from;
	//came_from[*start] = STRIPS();
	//
	//std::unordered_map<STRIPS, float> cost_so_far;
	//cost_so_far[*start] = 0;
	//
	//std::unordered_map<STRIPS, std::unordered_map<std::string, bool>> conditionsMap;
	//conditionsMap[*start] = conditions;
	//
	//STRIPS current = *start;
	//bool targetAccomplished = false;
	////current->cameFrom = nullptr;
	////current->costSoFar = 0;
	//
	//while (!frontier.empty())
	//{
	//	current = frontier.top().strips;
	//	frontier.pop();
	//	std::unordered_map<std::string, bool> currConditions = conditionsMap[current];
	//	if (currConditions[targetKey] == targetState) { targetAccomplished = true;  break; }
	//
	//	std::queue<STRIPS*> neighbors = current.neighbours;
	//	while (!neighbors.empty())
	//	{
	//		STRIPS next = *neighbors.front();
	//		neighbors.pop();
	//
	//		float new_cost = cost_so_far[current] + next.cost;
	//
	//		if ((cost_so_far[next] < 0 || new_cost < cost_so_far[next]) && next.ConditionsAccomplished(currConditions))
	//		{
	//			cost_so_far[next] = new_cost;
	//			float priority = new_cost;
	//			frontier.push(Priority_STRIPS(next, priority));
	//			came_from[next] = current;
	//			//conditionsMap[next] = next.GetNewConditions(conditionsMap[current]);
	//			conditionsMap[next] = currConditions;
	//			next.TriggerEffects(conditionsMap[next]);
	//		}
	//	}
	//}

	std::stack<STRIPS> path;

	//if (!targetAccomplished)
	//{
	//	//No path found!
	//}
	//else
	//{
	//	//Target found, reconstruct path that we took!
	//	STRIPS temp = current;
	//	path.push(temp);
	//	while (came_from[temp] != *start)
	//	{
	//		path.push(came_from[temp]);
	//		temp = came_from[temp];
	//	}
	//}


	return path;
}


