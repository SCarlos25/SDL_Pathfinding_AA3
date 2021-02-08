#include "ShootSTRIPS.h"

class ApproachEnemySTRIPS;
class ExploreSTRIPS;
class RunAwaySTRIPS;
class AimSTRIPS;

ShootSTRIPS::ShootSTRIPS() {
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
	neighbours.push(new ApproachEnemySTRIPS());
	neighbours.push(new ExploreSTRIPS());
	neighbours.push(new RunAwaySTRIPS());
	neighbours.push(new AimSTRIPS()); //?
}

void ShootSTRIPS::Update(Agent* agent) {
	// Shoot Behavior: kills target agent

	counter += inc;
	if (counter >= time_shooting)
	{
		counter = 0;

		// CHANGE BEHAVIOUR
	}
}