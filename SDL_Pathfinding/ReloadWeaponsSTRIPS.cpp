#include "ReloadWeaponSTRIPS.h"
#include "AimSTRIPS.h"
#include "RunAwaySTRIPS.h"
#include "ApproachSTRIPS.h"

ReloadWeaponSTRIPS::ReloadWeaponSTRIPS(bool initNeighbours = true) {
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
	neighbours.push(new AimSTRIPS(false));
	neighbours.push(new RunAwaySTRIPS(false));
	neighbours.push(new ApproachEnemySTRIPS(false));
}

void ReloadWeaponSTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze) {
	// Reload Behaviour: wait a second still and end behaviour

	counter += inc;
	if (counter >= time_reloading)
	{
		counter = 0;

		// CHANGE BEHAVIOUR
	}
}