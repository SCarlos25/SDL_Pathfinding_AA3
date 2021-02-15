#include "ApproachSTRIPS.h"
#include "ExploreStrips.h"
#include "AimSTRIPS.h"
#include "ReloadWeaponSTRIPS.h"
#include "Enemy.h"

ApproachEnemySTRIPS::ApproachEnemySTRIPS() {
	type = STRIPSTypes::APPROACH_ENEMY;
	cost = 1;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyVisible", true));
	conditions.insert(std::make_pair("enemyNearby", false));
	conditions.insert(std::make_pair("enemyAlive", true));
	conditions.insert(std::make_pair("enemyHasWeapon", false));

	// Init Effects
	effects.insert(std::make_pair("enemyNearby", true));
	effects.insert(std::make_pair("enemyVisible", true));

}

void ApproachEnemySTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* blackboard) {
	// Chase Behavior

	if (blackboard->conditions["enemyNearby"] && blackboard->conditions["enemyVisible"]
		|| blackboard->conditions["enemyHasWeapon"]) {
		agent->clearPath();
		agent->currAlgorithm->ChangeStrips(/*new AimSTRIPS(true)*/);
	}
	else if (Vector2D::Distance(enemy->getPosition(), lastEnemyPos) > refreshDistance) {
		if (blackboard->conditions["enemyVisible"]) {
			lastEnemyPos = enemy->getPosition();
			int n = 0; // contador de iteraciones de AStar
			agent->clearPath();

			path = PathFinding::AStar(maze, maze->pix2cell(agent->getPosition()), maze->pix2cell(enemy->getPosition()), n);
			while (!path.empty()) {
				agent->addPathPoint(maze->cell2pix(path.top().GetPos()));
				path.pop();
			}
		}
		else if(agent->getPathSize() == 0) {
			std::cout << "Explore\n";
			agent->currAlgorithm->ChangeStrips(/*new ExploreSTRIPS(true)*/);
		}
	}

}

void ApproachEnemySTRIPS::Init()
{
	std::cout << "\n---\nApproach" << std::endl;

	lastEnemyPos = Vector2D(-1, -1);
}

std::queue<STRIPS*> ApproachEnemySTRIPS::GetNeighbours()
{
	std::queue<STRIPS*> n;
	n.push(new ExploreSTRIPS());
	n.push(new AimSTRIPS());
	n.push(new ReloadWeaponSTRIPS());

	return n;
}