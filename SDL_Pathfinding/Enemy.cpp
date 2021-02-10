#include "Enemy.h"


void Enemy::Init(Vector2D pos)
{
	setPosition(pos);
}

void Enemy::SetTargetEnemy(Enemy *gTargetEnemy)
{
	targetEnemy = gTargetEnemy;
}

void Enemy::SetFiniteStateMachine()
{
	currAlgorithm = new FiniteStateMachine();
	currAlgorithm->Init(this, targetEnemy, maze);
	//currAlgorithm->Init();
}


void Enemy::UpdateEnemy()
{
	currAlgorithm->Update();
}