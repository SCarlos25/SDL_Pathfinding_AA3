#pragma once
#include "Enemy.h"
#include <unordered_map>
#include <stack>
#include <queue>
#include "Priority_STRIPS.h"

class Blackboard {
public:
	std::unordered_map<std::string, bool> conditions;

	Blackboard()
	{
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("hasWeapon", true));
		conditions.insert(std::make_pair("loadedWeapon", true));
		conditions.insert(std::make_pair("hasBomb", true));
		conditions.insert(std::make_pair("aiming", false));

		conditions.insert(std::make_pair("enemyVisible", false));
		conditions.insert(std::make_pair("enemyAligned", false));
		conditions.insert(std::make_pair("enemyNearby", false));
		conditions.insert(std::make_pair("enemyAlive", true));
		conditions.insert(std::make_pair("enemyHasGun", true));
	}

	std::stack<STRIPS> GOAP_AStar(STRIPS* start, std::string targetKey, bool targetState);

};