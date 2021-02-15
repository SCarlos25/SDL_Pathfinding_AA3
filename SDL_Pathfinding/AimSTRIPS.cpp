#include "AimSTRIPS.h"
#include "ShootSTRIPS.h"
#include "ReloadWeaponSTRIPS.h"
#include <time.h>
//#include <clock.h>
#include "Enemy.h"
//#include "GOAP.h"

AimSTRIPS::AimSTRIPS() {
	type = STRIPSTypes::AIM;
	cost = 0;

	//counter = 0;
	//aimingTime = 2.0f;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyVisible", true));
	conditions.insert(std::make_pair("enemyNearby", true));
	conditions.insert(std::make_pair("enemyAlive", true));
	conditions.insert(std::make_pair("hasWeapon", true));
	conditions.insert(std::make_pair("loadedWeapon", true));
	conditions.insert(std::make_pair("aiming", false));

	// Init Effects
	effects.insert(std::make_pair("aiming", true));

}

void AimSTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* blackboard) {
	// Aim Behavior: wait a second and, if still on range, change to ShootSTRIPS

	//if (blackboard->conditions["loadedWeapon"])
	//{
	//	agent->currAlgorithm->ChangeStrips(/*new ShootSTRIPS(true)*/);
	//}
	//else
	//{
	//	agent->currAlgorithm->ChangeStrips(/*new ReloadWeaponSTRIPS(true)*/);
	//}

	Vector2D orientationDir = Vector2D(enemy->getPosition().x - agent->getPosition().x, enemy->getPosition().y - agent->getPosition().y);
	agent->setOrientation(orientationDir);

	if (!blackboard->conditions["enemyVisible"] || !blackboard->conditions["enemyNearby"] || blackboard->conditions["enemyHasWeapon"]) {
		agent->currAlgorithm->ChangeStrips();
	}

	std::cout << "currTime: " << currTime << std::endl;
	if (currTime > aimingDelay) {
		if(blackboard->conditions["enemyVisible"] && blackboard->conditions["enemyNearby"])
			blackboard->conditions["aiming"] = true;
		agent->currAlgorithm->ChangeStrips();
	}

	currTime += Scene::deltaTime;

}

void AimSTRIPS::Init()
{
	std::cout << "\n---\nAim" << std::endl;

	currTime = 0;
}

std::queue<STRIPS*> AimSTRIPS::GetNeighbours()
{
	std::queue<STRIPS*> n;
	n.push(new ShootSTRIPS());
	//n.push(new ReloadWeaponSTRIPS());

	return n;
}