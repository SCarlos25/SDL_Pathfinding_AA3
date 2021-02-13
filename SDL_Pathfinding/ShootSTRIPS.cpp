#include "ShootSTRIPS.h"
#include "ApproachSTRIPS.h"
#include "ExploreSTRIPS.h"
#include "RunAwaySTRIPS.h"
#include "AimSTRIPS.h"

ShootSTRIPS::ShootSTRIPS(bool initNeighbours = true) {
	type = STRIPSTypes::SHOOT;
	cost = 1;

	counter = 0;
	time_shooting = 1.0f;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyVisible", false));
	conditions.insert(std::make_pair("enemyNearby", false));
	conditions.insert(std::make_pair("enemyAlive", true));
	conditions.insert(std::make_pair("enemyHasGun", false));
	conditions.insert(std::make_pair("hasWeapon", true));
	conditions.insert(std::make_pair("aiming", true));
	conditions.insert(std::make_pair("loadedWeapon", true));

	// Init Effects
	effects.insert(std::make_pair("loadedWeapon", false));
	effects.insert(std::make_pair("enemyAlive", false));

	// Init neighbors
	neighbours = std::queue<STRIPS*>();
	neighbours.push(new ApproachEnemySTRIPS(false));
	neighbours.push(new ExploreSTRIPS(false));
	neighbours.push(new RunAwaySTRIPS(false));
	neighbours.push(new AimSTRIPS(false)); //?
}

void ShootSTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* blackboard) {
	// Shoot Behavior: kills target agent

	counter += inc;
	if (counter >= time_shooting)
	{
		counter = 0;

		// CHANGE BEHAVIOUR
	}
}