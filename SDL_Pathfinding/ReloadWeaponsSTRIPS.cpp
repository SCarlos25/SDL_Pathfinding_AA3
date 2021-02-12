#include "ReloadWeaponSTRIPS.h"
#include "AimSTRIPS.h"
#include "RunAwaySTRIPS.h"
#include "ApproachSTRIPS.h"
#include "ShootSTRIPS.h"
#include "ExploreSTRIPS.h"
#include "Enemy.h"

ReloadWeaponSTRIPS::ReloadWeaponSTRIPS(bool initNeighbours = true) {
	type = STRIPSTypes::RELOAD;
	cost = 2;

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
	//neighbours.push(new AimSTRIPS(false));
	//neighbours.push(new RunAwaySTRIPS(false));
	neighbours.push(new ShootSTRIPS(false));
	neighbours.push(new ApproachEnemySTRIPS(false));
	neighbours.push(new ExploreSTRIPS(false));
}

void ReloadWeaponSTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze) {
	// Reload Behaviour: wait a second still and end behaviour

	if (clock() >= goalTime)
	{
		agent->loadedWeapon = true;

		// CHANGE BEHAVIOUR
		if (Blackboard::GetInstance()->conditions["enemyNearby"]
			&& Blackboard::GetInstance()->conditions["enemyVisible"]) {
			agent->currAlgorithm->ChangeStrips(new ShootSTRIPS(true));
		}
		else if (Blackboard::GetInstance()->conditions["enemyVisible"]) {
			agent->currAlgorithm->ChangeStrips(new ApproachEnemySTRIPS(true));
		}
		else {
			agent->currAlgorithm->ChangeStrips(new ExploreSTRIPS(true));
		}
	}
}

void ReloadWeaponSTRIPS::Init()
{
	goalTime = clock() + reloadingDelay;
}
