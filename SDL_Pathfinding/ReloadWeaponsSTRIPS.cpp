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
	conditions.insert(std::make_pair("enemyVisible", true));
	conditions.insert(std::make_pair("enemyNearby", true));
	conditions.insert(std::make_pair("hasWeapon", true));
	conditions.insert(std::make_pair("loadedWeapon", false));
	//conditions.insert(std::make_pair("aiming", true));

	// Init Effects
	effects.insert(std::make_pair("loadedWeapon", true));
	//conditions.insert(std::make_pair("aiming", true));
	//conditions.insert(std::make_pair("hasWeapon", true));

	// Init neighbors
	//neighbours = std::queue<STRIPS*>();
	//neighbours.push(new AimSTRIPS(false));
	//neighbours.push(new RunAwaySTRIPS(false));
	if (initNeighbours)
	{
		//neighbours.push(new ShootSTRIPS(false));
		neighbours.push(new AimSTRIPS(false));
		neighbours.push(new ApproachEnemySTRIPS(false));
		neighbours.push(new ExploreSTRIPS(false));
	}
}

void ReloadWeaponSTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* blackboard) {
	// Reload Behaviour: wait a second still and end behaviour

	if (blackboard->conditions["enemyVisible"]) {
		Vector2D orientationDir = Vector2D(enemy->getPosition().x - agent->getPosition().x, enemy->getPosition().y - agent->getPosition().y);
		agent->setOrientation(orientationDir);
	}
	if (blackboard->conditions["enemyHasWeapon"]) {
		agent->clearPath();
		agent->currAlgorithm->ChangeStrips();
	}

	std::cout << "currTime: " << currTime << std::endl;
	if (currTime > reloadingDelay)
	{
		agent->loadedWeapon = true;
		agent->currAlgorithm->ChangeStrips();

		// CHANGE BEHAVIOUR
		//if (blackboard->conditions["enemyNearby"]
		//	&& blackboard->conditions["enemyVisible"]) {
		//	agent->currAlgorithm->ChangeStrips(/*new ShootSTRIPS(true)*/);
		//}
		//else if (blackboard->conditions["enemyVisible"]) {
		//	agent->currAlgorithm->ChangeStrips(/*new ApproachEnemySTRIPS(true)*/);
		//}
		//else {
		//	agent->currAlgorithm->ChangeStrips(/*new ExploreSTRIPS(true)*/);
		//}
	}

	currTime += Scene::deltaTime;
}

void ReloadWeaponSTRIPS::Init()
{
	std::cout << "\n---\nReload" << std::endl;

	currTime = 0;

}

std::queue<STRIPS*> ReloadWeaponSTRIPS::GetNeighbours()
{
	std::queue<STRIPS*> n;
	//n.push(new ShootSTRIPS(true));
	n.push(new AimSTRIPS(false));
	n.push(new ApproachEnemySTRIPS(true));
	n.push(new ExploreSTRIPS(true));

	return n;
}