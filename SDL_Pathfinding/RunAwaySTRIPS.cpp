#include "RunAwaySTRIPS.h"
#include "ExploreSTRIPS.h"
#include "ApproachSTRIPS.h"
#include "Enemy.h"

RunAwaySTRIPS::RunAwaySTRIPS(bool initNeighbours = true) {
	type = STRIPSTypes::RUN_AWAY;
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
	neighbours.push(new ExploreSTRIPS(false));
	//neighbours.push(new ApproachEnemySTRIPS(false));
}

void RunAwaySTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze) {
	// Flee Behavior o Random target con A*?

	if (Blackboard::GetInstance()->conditions["enemyNearby"]
		&& Blackboard::GetInstance()->conditions["enemyVisible"]) {
		//if (/*weapon nearby*/) {
		//	// look for weapon
		//}
		if (Vector2D::Distance(enemy->getPosition(), lastEnemyPos) > refreshDistance) {
			lastEnemyPos = enemy->getPosition();
			int n = 0;
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

			path = PathFinding::Greedy(maze, maze->pix2cell(agent->getPosition()), target, n); // getTarget() no se si esta en modo pixel o en modo cell
			while (!path.empty()) {
				agent->addPathPoint(maze->cell2pix(path.top().GetPos()));
				path.pop();
			}
		}
	}
	else {
		agent->currAlgorithm->ChangeStrips(new ExploreSTRIPS(true));
	}
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
