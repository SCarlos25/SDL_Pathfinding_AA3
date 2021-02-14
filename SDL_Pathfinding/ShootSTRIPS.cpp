#include "ShootSTRIPS.h"
#include "ApproachSTRIPS.h"
#include "ExploreSTRIPS.h"
#include "RunAwaySTRIPS.h"
#include "AimSTRIPS.h"
#include "Enemy.h"

ShootSTRIPS::ShootSTRIPS(bool initNeighbours = true) {
	type = STRIPSTypes::SHOOT;
	cost = 1;

	counter = 0;
	time_shooting = clock() + 1;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyVisible", true));
	conditions.insert(std::make_pair("enemyNearby", true));
	conditions.insert(std::make_pair("enemyAlive", true));
	conditions.insert(std::make_pair("hasWeapon", true));
	conditions.insert(std::make_pair("aiming", true));
	conditions.insert(std::make_pair("loadedWeapon", true));

	// Init Effects
	effects.insert(std::make_pair("loadedWeapon", false));
	effects.insert(std::make_pair("enemyAlive", false));

	// Init neighbors
	//neighbours = std::queue<STRIPS*>();
	if (initNeighbours)
	{
		neighbours.push(new ApproachEnemySTRIPS(false));
		neighbours.push(new ExploreSTRIPS(false));
		neighbours.push(new RunAwaySTRIPS(false));
		neighbours.push(new AimSTRIPS(false)); //?
	}
}

void ShootSTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* blackboard) {
	// Shoot Behavior: kills target agent

	if (clock() >= time_shooting)
	{
		// CHANGE BEHAVIOUR
		agent->currAlgorithm->ChangeStrips(new ExploreSTRIPS(true));
	}
}

std::queue<STRIPS*> ShootSTRIPS::GetNeighbours()
{
	std::queue<STRIPS*> n;
	n.push(new ApproachEnemySTRIPS(true));
	n.push(new ExploreSTRIPS(true));
	n.push(new RunAwaySTRIPS(true));
	n.push(new AimSTRIPS(true)); //?

	return n;
}