#include "RunAwaySTRIPS.h"

class ExploreSTRIPS;
class ApproachEnemySTRIPS;

RunAwaySTRIPS::RunAwaySTRIPS() {
	cost = 1;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyAlive", true));
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyHasGun", true));
	conditions.insert(std::make_pair("hasWeapon", false));

	// Init Effects
	effects.insert(std::make_pair("enemyNearby", false));
	effects.insert(std::make_pair("enemyVisible", false));

	// Init neighbors
	neighbours = std::queue<STRIPS*>();
	neighbours.push(new ExploreSTRIPS());
	neighbours.push(new ApproachEnemySTRIPS());
}

void RunAwaySTRIPS::Update(Agent* agent, Grid* maze) {
	// Flee Behavior o Random target con A*?
	float dist, min_dist = 2;
	int n = 0;

	Vector2D target = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	dist = Vector2D::Distance(maze->pix2cell(agent->getPosition()), target);

	while (!maze->isValidCell(target) && dist > min_dist)
	{
		target = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	}

	path = PathFinding::AStar(maze, maze->pix2cell(agent->getPosition()), target, n); // getTarget() no se si esta en modo pixel o en modo cell
	while (!path.empty()) {
		agent->addPathPoint(maze->cell2pix(path.top().GetPos()));
		path.pop();
	}
}