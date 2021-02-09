#pragma once
#include <unordered_map>
#include <stack>
#include <cmath>
#include <ctime>
#include <time.h>
#include <queue>

#include "../src/PathFinding.h"

class STRIPS;

class Blackboard {
public:
	static std::unordered_map<std::string, bool> conditions;
	const float AGENT_RANGE = 150;

	Blackboard()
	{
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("hasWeapon", true));
		conditions.insert(std::make_pair("loadedWeapon", true));
		conditions.insert(std::make_pair("hasBomb", true));
		
		conditions.insert(std::make_pair("enemyVisible", false));
		//conditions.insert(std::make_pair("enemyAligned", false));
		conditions.insert(std::make_pair("enemyNearby", false));
		conditions.insert(std::make_pair("enemyAlive", true));
		conditions.insert(std::make_pair("enemyHasWeapon", false));
		conditions.insert(std::make_pair("enemyHasBomb", false));
	}

	void UpdateConditionsState(Ally* ally, Enemy* enemy);

	static std::stack<STRIPS> GOAP_AStar(STRIPS* start, std::string targetKey, bool targetState);

};
