#include "Enemy.h"

void Enemy::Init(Vector2D pos)
{
	setPosition(pos);
}

void Enemy::SetTargetEnemy(Enemy *gTargetEnemy)
{
	targetEnemy = gTargetEnemy;
}

void Enemy::SetFiniteStateMachine(Blackboard* blackboard)
{
	currAlgorithm = new FiniteStateMachine();
	currAlgorithm->Init(this, targetEnemy, maze, blackboard);
	//currAlgorithm->Init();
}

void Enemy::SetGOAP(Blackboard* blackboard)
{
	currAlgorithm = new GOAP();
	currAlgorithm->Init(this, targetEnemy, maze, blackboard);
	//currAlgorithm->Init();
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