#include "ReloadWeaponSTRIPS.h"
#include "AimSTRIPS.h"
#include "RunAwaySTRIPS.h"
#include "ApproachSTRIPS.h"
#include "ShootSTRIPS.h"
#include "ExploreSTRIPS.h"
#include "Enemy.h"

ReloadWeaponSTRIPS::ReloadWeaponSTRIPS() {
	type = STRIPSTypes::RELOAD;
	cost = 2;
	name = "Reload";

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyVisible", true));
	conditions.insert(std::make_pair("enemyNearby", true));
	conditions.insert(std::make_pair("hasWeapon", true));
	conditions.insert(std::make_pair("loadedWeapon", false));
	//conditions.insert(std::make_pair("aiming", true));

	// Init Effects
	effects.insert(std::make_pair("loadedWeapon", true));

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

	//std::cout << "currTime: " << currTime << std::endl;
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
	//n.push(new ShootSTRIPS());
	n.push(new AimSTRIPS());
	n.push(new ApproachEnemySTRIPS());
	n.push(new ExploreSTRIPS());

	return n;
}