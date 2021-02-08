#include "ReloadWeaponSTRIPS.h"

class AimSTRIPS;
class RunAwaySTRIPS;
class ApproachEnemySTRIPS;

ReloadWeaponSTRIPS::ReloadWeaponSTRIPS() {
	cost = 2;

	counter = 0;
	time_reloading = 3.0f;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("hasWeapon", true));
	conditions.insert(std::make_pair("loadedWeapon", false));
	conditions.insert(std::make_pair("aiming", true));
	conditions.insert(std::make_pair("enemyHasGun", false));

	// Init Effects
	effects.insert(std::make_pair("loadedWeapon", true));

	// Init neighbors
	neighbours = std::queue<STRIPS*>();
	neighbours.push(new AimSTRIPS());
	neighbours.push(new RunAwaySTRIPS());
	neighbours.push(new ApproachEnemySTRIPS());
}

void ReloadWeaponSTRIPS::Update(Agent* agent) {
	// Reload Behaviour: wait a second still and end behaviour

	counter += inc;
	if (counter >= time_reloading)
	{
		counter = 0;

		// CHANGE BEHAVIOUR
	}
}