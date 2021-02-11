#include "ApproachSTRIPS.h"
#include "ExploreStrips.h"
#include "Enemy.h"

ApproachEnemySTRIPS::ApproachEnemySTRIPS(bool initNeighbours = true) {
	type = STRIPSTypes::APPROACH_ENEMY;
	cost = 1;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyVisible", false));
	conditions.insert(std::make_pair("enemyNearby", false));
	conditions.insert(std::make_pair("enemyAlive", true));
	conditions.insert(std::make_pair("enemyHasGun", false));

	// Init Effects
	effects.insert(std::make_pair("enemyNearby", true));

	// Init neighbors
	neighbours = std::queue<STRIPS*>();
	//neighbours.push(new AimSTRIPS());
	if (initNeighbours)
	{
		neighbours.push(new ExploreSTRIPS(false));
	}
	//neighbours.push(new RunAwaySTRIPS());
	//neighbours.push(new DetonateBombSTRIPS());
}

void ApproachEnemySTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze) {
	// Chase Behavior
	int n = 0; // ?

	path = PathFinding::AStar(maze, maze->pix2cell(agent->getPosition()), maze->pix2cell(enemy->getPosition()), n);
	while (!path.empty()) {
		agent->addPathPoint(maze->cell2pix(path.top().GetPos()));
		path.pop();
	}
}