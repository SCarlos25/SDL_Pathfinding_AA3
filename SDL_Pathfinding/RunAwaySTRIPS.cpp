#include "RunAwaySTRIPS.h"
#include "ExploreSTRIPS.h"
#include "ApproachSTRIPS.h"
#include "Enemy.h"

RunAwaySTRIPS::RunAwaySTRIPS() {
	type = STRIPSTypes::RUN_AWAY;
	cost = 1;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("enemyAlive", true));
	conditions.insert(std::make_pair("enemyHasWeapon", true));
	//conditions.insert(std::make_pair("hasWeapon", false));

	// Init Effects
	effects.insert(std::make_pair("enemyNearby", false));
	effects.insert(std::make_pair("enemyVisible", false));
	effects.insert(std::make_pair("enemyHasWeapon", false));

}

void RunAwaySTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* blackboard) {
	// Flee Behavior o Random target con A*?

	if (blackboard->conditions["enemyNearby"] || blackboard->conditions["enemyVisible"]) {
		if (!blackboard->conditions["enemyHasWeapon"]) {
			agent->clearPath();
			agent->currAlgorithm->ChangeStrips(/*new ExploreSTRIPS(true)*/);
		}
		else if (agent->getPathSize() == 0) {
			lastEnemyPos = enemy->getPosition();
			int n = 0;
			agent->clearPath();

			Vector2D agentMargins = Vector2D(maze->pix2cell(agent->getPosition()));
			Vector2D enemyMargins = Vector2D(maze->pix2cell(enemy->getPosition()));

			Vector2D target = Vector2D((float)(rand() % (int)(maze->getNumCellX() - enemyMargins.x)),
				(float)(rand() % (int)(maze->getNumCellY() - enemyMargins.y)));
			target = GetFinalTarget(target, agentMargins, enemyMargins);
			//dist = Vector2D::Distance(maze->pix2cell(agent->getPosition()), target);

			while (!maze->isValidCell(target))
			{
				target = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
				target = GetFinalTarget(target, agentMargins, enemyMargins);
			}

			path = PathFinding::AStar(maze, maze->pix2cell(agent->getPosition()), target, n); // getTarget() no se si esta en modo pixel o en modo cell
			while (!path.empty()) {
				agent->addPathPoint(maze->cell2pix(path.top().GetPos()));
				path.pop();
			}
		}
	}
	else {
		agent->clearPath();
		agent->currAlgorithm->ChangeStrips(/*new ExploreSTRIPS(true)*/);
	}
}

void RunAwaySTRIPS::Init()
{
	std::cout << "\n---\nRun Away" << std::endl;

	lastEnemyPos = Vector2D(-1, -1);
}

Vector2D RunAwaySTRIPS::GetFinalTarget(Vector2D target, const Vector2D &currPos, const Vector2D & enemyMargins)
{
	if (enemyMargins.x < currPos.x) {
		target.x += enemyMargins.x;
	}

	if (enemyMargins.y < currPos.y) {
		target.y += enemyMargins.y;
	}

	return target;
}

std::queue<STRIPS*> RunAwaySTRIPS::GetNeighbours()
{
	std::queue<STRIPS*> n;
	n.push(new ExploreSTRIPS());

	return n;
}