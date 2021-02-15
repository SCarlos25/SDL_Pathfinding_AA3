#include "Flee_Behaviour.h"
#include "Wander_Behaviour.h"
#include "Chase_Behaviour.h"
#include "Raycast.h"
#include "FiniteStateMachine.h"
#include "../SDL_Pathfinding/Enemy.h"
#include "../src/ScenePathFindingMouse.h"
#include "../src/utils.h"
#include <iostream>

void FleeBehaviour::Init()
{

}

void FleeBehaviour::Update()
{
	//If we lose vision with the enemy go back to wanderbehaviour
	if (Raycast::RaycastCollidesWall(machineState->agentBase->getPosition(), machineState->enemyAgent->getPosition(), machineState->maze))
	{
		std::cout << "--------------------------\n";
		std::cout << "SFM STATUS: WANDERBEHAVIOUR\n";
		std::cout << "EnemySpotted == false\n";
		if (machineState->enemyAgent->hasWeapon)
		{
			std::cout << "EnemyHasWeapon == true\n";
		}
		else
		{
			std::cout << "EnemyHasWeapon == false\n";
		}
		std::cout << "--------------------------\n";
		machineState->currBehaviour = new WanderBehaviour(machineState);
		Exit();
		return;
	}

	//If our chaser has no gun, then go back to chasing him instead!
	if (!machineState->enemyAgent->hasWeapon)
	{
		std::cout << "--------------------------\n";
		std::cout << "SFM STATUS: CHASEBEHAVIOUR\n";
		std::cout << "EnemySpotted == true\n";
		std::cout << "EnemyHasWeapon == false\n";
		std::cout << "--------------------------\n";
		machineState->currBehaviour = new ChaseBehaviour(machineState);
		Exit();
		return;
	}

	//If we finished our path 
	if (machineState->agentBase->getPathSize() == 0)
	{
		//Vector2D wanderDir = (machineState->agentBase->getPosition() - machineState->enemyAgent->getPosition()).Normalize() * 350;
		Vector2D wanderPos = machineState->agentBase->getPosition();
		wanderPos.x = RandomNumber(-1, 1);
		wanderPos.y = RandomNumber(-1, 1);
		wanderPos.x = RandomNumber(240, 300) * wanderPos.x;
		wanderPos.y = RandomNumber(240, 300) * wanderPos.y;
		machineState->agentBase->SetWalkPoint(machineState->agentBase->getPosition() + wanderPos);
	}
}

void FleeBehaviour::Exit()
{
	delete this;
}