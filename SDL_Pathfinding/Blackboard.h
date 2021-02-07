#pragma once
#include "Enemy.h"
#include "STRIPS.h"
#include "Priority_STRIPS.h"
#include <unordered_map>
#include <stack>
#include <queue>

class Blackboard {
public:
	std::unordered_map<std::string, bool> conditions;

	Blackboard()
	{
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("hasWeapon", true));
		conditions.insert(std::make_pair("loadedWeapon", true));
		conditions.insert(std::make_pair("hasBomb", true));

		conditions.insert(std::make_pair("enemyVisible", false));
		conditions.insert(std::make_pair("enemyAligned", false));
		conditions.insert(std::make_pair("enemyNearby", false));
		conditions.insert(std::make_pair("enemyAlive", true));
	}

	void CheckEnemy(Enemy enemy)
	{
		
	}

	std::stack<STRIPS> GOAP_AStar(STRIPS* start, std::string targetKey, bool targetState);

};
