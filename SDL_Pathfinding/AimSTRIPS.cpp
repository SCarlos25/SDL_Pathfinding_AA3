#include "AimSTRIPS.h"

class ShootSTRIPS;
class ReloadWeaponSTRIPS;

AimSTRIPS::AimSTRIPS() {
	cost = 0;

	counter = 0;
	time_aiming = 2.0f;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyVisible", false));
	conditions.insert(std::make_pair("enemyNearby", false));
	conditions.insert(std::make_pair("enemyAlive", true));
	conditions.insert(std::make_pair("enemyHasGun", false));
	conditions.insert(std::make_pair("hasWeapon", true));
	conditions.insert(std::make_pair("aiming", false));
	conditions.insert(std::make_pair("loadedWeapon", true));

	// Init Effects
	effects.insert(std::make_pair("aiming", true));

	// Init neighbors
	neighbours = std::queue<STRIPS*>();
	neighbours.push(new ShootSTRIPS());
	neighbours.push(new ReloadWeaponSTRIPS());
}

void AimSTRIPS::Update(Agent* agent) {
	// Aim Behavior: wait a second and, if still on range, change to ShootSTRIPS

	counter += inc; // inc NO, clock.deltaTime

	if (counter >= time_aiming)
	{
		counter = 0;

		// Done
	}
}