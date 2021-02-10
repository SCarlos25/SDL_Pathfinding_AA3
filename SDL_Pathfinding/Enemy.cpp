#include "Enemy.h"

Enemy::Enemy() {}

void Enemy::Init(Vector2D pos)
{
	setPosition(pos);
}

void Enemy::SetFiniteStateMachine()
{
	currAlgorithm = new FiniteStateMachine();
	//currAlgorithm->Init();
}

void Enemy::UpdateEnemy()
{
	currAlgorithm->Update();
}