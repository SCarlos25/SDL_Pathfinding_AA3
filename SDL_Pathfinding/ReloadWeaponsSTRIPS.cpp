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
	//conditions.insert(std::make_pair("aiming", true));

	// Init Effects
	effects.insert(std::make_pair("loadedWeapon", true));

	// Init neighbors
	//neighbours = std::queue<STRIPS*>();
	//neighbours.push(new AimSTRIPS(false));
	//neighbours.push(new RunAwaySTRIPS(false));
	if (initNeighbours)
	{
		neighbours.push(new ShootSTRIPS(false));
		neighbours.push(new ApproachEnemySTRIPS(false));
		neighbours.push(new ExploreSTRIPS(false));
	}
}

void ReloadWeaponSTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* blackboard) {
	// Reload Behaviour: wait a second still and end behaviour

	if (clock() >= goalTime)
	{
		agent->loadedWeapon = true;

		// CHANGE BEHAVIOUR
		if (blackboard->conditions["enemyNearby"]
			&& blackboard->conditions["enemyVisible"]) {
			agent->currAlgorithm->ChangeStrips(/*new ShootSTRIPS(true)*/);
		}
		else if (blackboard->conditions["enemyVisible"]) {
			agent->currAlgorithm->ChangeStrips(/*new ApproachEnemySTRIPS(true)*/);
		}
		else {
			agent->currAlgorithm->ChangeStrips(/*new ExploreSTRIPS(true)*/);
		}
	}
}

void ReloadWeaponSTRIPS::Init()
{
	goalTime = clock() + reloadingDelay;
}

std::queue<STRIPS*> ReloadWeaponSTRIPS::GetNeighbours()
{
	std::queue<STRIPS*> n;
	n.push(new ShootSTRIPS(true));
	n.push(new ApproachEnemySTRIPS(true));
	n.push(new ExploreSTRIPS(true));

	return n;
}