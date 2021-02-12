#pragma once
#include <unordered_map>
#include <stack>
#include <cmath>
#include <ctime>
#include <time.h>
#include <queue>

#include "../src/PathFinding.h"

class Blackboard {
public:
	static Blackboard *instance;

	std::unordered_map<std::string, bool> conditions;
	const float AGENT_RANGE = 150;

	Blackboard();

	static Blackboard* GetInstance() {
		if (instance == nullptr)
		{
			instance = new Blackboard();
		}

		return instance;
	}

	void UpdateConditionsState(Enemy* ally, Enemy* enemy, Grid *maze);


};
