#include "ApproachSTRIPS.h"
#include "ExploreStrips.h"
#include "AimSTRIPS.h"
#include "Enemy.h"

ApproachEnemySTRIPS::ApproachEnemySTRIPS(bool initNeighbours = true) {
	type = STRIPSTypes::APPROACH_ENEMY;
	cost = 1;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyVisible", false));
	conditions.insert(std::make_pair("enemyNearby", false));
	conditions.insert(std::make_pair("enemyAlive", true));
	//conditions.insert(std::make_pair("enemyHasGun", false));

	// Init Effects
	effects.insert(std::make_pair("enemyNearby", true));
	effects.insert(std::make_pair("enemyVisible", true));

	// Init neighbors
	//neighbours = std::queue<STRIPS*>();
	//neighbours.push(new AimSTRIPS());
	if (initNeighbours)
	{
		neighbours.push(new ExploreSTRIPS(false));
		neighbours.push(new AimSTRIPS(false));
	}
	//neighbours.push(new RunAwaySTRIPS());
	//neighbours.push(new DetonateBombSTRIPS());
}

void ApproachEnemySTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* blackboard) {
	// Chase Behavior

	if (blackboard->conditions["enemyNearby"]
		&& blackboard->conditions["enemyVisible"]) {
		agent->currAlgorithm->ChangeStrips(new AimSTRIPS(true));
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
		else {
			agent->currAlgorithm->ChangeStrips(new ExploreSTRIPS(true));
		}
	}
}

std::queue<STRIPS*> ApproachEnemySTRIPS::GetNeighbours()
{
	std::queue<STRIPS*> n;
	n.push(new ExploreSTRIPS(true));
	n.push(new AimSTRIPS(true));

	return n;
}