#pragma once
#include "Enemy.h"

class Blackboard {
public:
	bool agentAlive = true;
	bool hasWeapon;
	bool loadedWeapon;
	bool hasBomb;

	bool enemyVisible = false;
	bool enemyAligned = false;
	bool enemyNearby;
	bool enemyAlive = true;

	void CheckEnemy(Enemy enemy)
	{
		
	}

};
