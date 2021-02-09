#include "Enemy.h"


void Enemy::Init(Vector2D pos)
{
	setPosition(pos);
}

void Enemy::SetFiniteStateMachine()
{
	currAlgorithm = new FiniteStateMachine();
	currAlgorithm->Init(this);
}

void Enemy::UpdateEnemy(Enemy* enemyAgent, Grid *maze)
{
	currAlgorithm->Update(enemyAgent, maze);
}