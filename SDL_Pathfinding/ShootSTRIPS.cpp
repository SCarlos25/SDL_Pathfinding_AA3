#include "ShootSTRIPS.h"
#include "ApproachSTRIPS.h"
#include "ExploreSTRIPS.h"
#include "RunAwaySTRIPS.h"
#include "AimSTRIPS.h"

ShootSTRIPS::ShootSTRIPS() {
	type = STRIPSTypes::SHOOT;
	cost = 1;
	name = "Shoot";

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

}

void ShootSTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* blackboard) {
	// Shoot Behavior: kills target agent

	//std::cout << "currTime: " << currTime << std::endl;
	if (currTime > shootingDelay) {
		blackboard->conditions["enemyAlive"] = false;
		blackboard->conditions["loadedWeapon"] = false;

		std::cout << "\nROBOT WINS!\nPress Esc/Q to quit...\n";
		Scene::pause = true;
		//system("PAUSE");
	}

	currTime += Scene::deltaTime;

	/*counter += inc;
	if (counter >= time_shooting)
	{
		counter = 0;

		// CHANGE BEHAVIOUR
	}*/
}

void ShootSTRIPS::Init()
{
	std::cout << "\n---\nShoot" << std::endl;

	currTime = 0;
}

std::queue<STRIPS*> ShootSTRIPS::GetNeighbours()
{
	std::queue<STRIPS*> n;
	n.push(new ApproachEnemySTRIPS());
	n.push(new ExploreSTRIPS());
	n.push(new RunAwaySTRIPS());
	n.push(new AimSTRIPS()); //?

	return n;
}