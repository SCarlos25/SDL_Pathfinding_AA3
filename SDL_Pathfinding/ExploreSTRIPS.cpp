#include "ExploreSTRIPS.h"
#include "ApproachSTRIPS.h"
#include "RunAwaySTRIPS.h"
#include "Enemy.h"

ExploreSTRIPS::ExploreSTRIPS(bool initNeighbours = true) {
	type = STRIPSTypes::EXPLORE;
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
	if (initNeighbours)
	{
		neighbours.push(new ApproachEnemySTRIPS(false));
		neighbours.push(new RunAwaySTRIPS(false));
	}
	//neighbours.push(new DetonateBombSTRIPS());
}

void ExploreSTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* blackboard) {
	// Wander Behavior

	//if
	// distance(e1, e2) < x
	// se queda sin puntos a los que ir
	// distance(e1, maze->weapon) < y

	if (blackboard->conditions["enemyVisible"]) {
		if ((blackboard->conditions["enemyHasWeapon"] || blackboard->conditions["enemyHasBomb"])
			&& (!blackboard->conditions["hasWeapon"] && !blackboard->conditions["hasBomb"])) {
			agent->currAlgorithm->ChangeStrips(new RunAwaySTRIPS(true));
		}
		else if (blackboard->conditions["hasWeapon"] || blackboard->conditions["hasBomb"]) {
			agent->currAlgorithm->ChangeStrips(new ApproachEnemySTRIPS(true));
		}
	}
	//else if (/*has weapon nearby*/) {
	//	// approach weapon
	//}
	else if (agent->getPathSize() == 0)
	{
		int n = 0; //  contador de iteraciones de AStar
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