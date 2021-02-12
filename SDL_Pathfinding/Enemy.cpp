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
}

void Enemy::UpdateEnemy()
{
	currAlgorithm->Update();
}

void Enemy::GiveGun()
{
	hasGun = true;
}

void Enemy::TakeGun()
{
	hasGun = false;
}