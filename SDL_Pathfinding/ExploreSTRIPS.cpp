#include "ExploreSTRIPS.h"
#include "ApproachSTRIPS.h"

ExploreSTRIPS::ExploreSTRIPS() {
	id = "Explore";
	cost = 0;

	arrived = false;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyVisible", false));
	conditions.insert(std::make_pair("enemyNearby", false));

	// Init Effects
	// ...

	// Init neighbors
	neighbours = std::queue<STRIPS*>();
	neighbours.push(new ApproachEnemySTRIPS());
	//neighbours.push(new DetonateBombSTRIPS());
}

void ExploreSTRIPS::Update(Agent* agent, Grid* maze) {
	// Wander Behavior
	if (agent->getPathSize() == 0)
	{
		int n = 0; // ?
		Vector2D target = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		while (!maze->isValidCell(target))
		{
			target = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		}

		path = PathFinding::AStar(maze, maze->pix2cell(agent->getPosition()), target, n); // getTarget() no se si esta en modo pixel o en modo cell
		while (!path.empty()) {
			agent->addPathPoint(maze->cell2pix(path.top().GetPos()));
			path.pop();
		}
	}
}