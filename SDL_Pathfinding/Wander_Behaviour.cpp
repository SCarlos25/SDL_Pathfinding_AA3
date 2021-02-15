#include "Wander_Behaviour.h"
#include "Chase_Behaviour.h"
#include "FiniteStateMachine.h"
#include "../SDL_Pathfinding/Enemy.h"
#include "../src/ScenePathFindingMouse.h"
#include "../src/utils.h"
#include "Raycast.h"
#include <iostream>

void WanderBehaviour::Init()
{

}

void WanderBehaviour::Update()
{
	currTime = currTime + Scene::deltaTime;
	//If the time delay has passed and we dont have a path, then make a new path and walk to it
	if (currTime > futWanderTime &&  (machineState->agentBase->getPathSize() == 0))
	{
		futWanderTime = minWanderDelay + (rand() % (maxWanderDelay - minWanderDelay));
		currTime = 0;
		Vector2D wanderPos = machineState->agentBase->getPosition();
		wanderPos.x = RandomNumber(-1,1);
		wanderPos.y = RandomNumber(-1,1);
		wanderPos.x = RandomNumber(minWanderRange, maxWanderRange) * wanderPos.x;
		wanderPos.y = RandomNumber(minWanderRange, maxWanderRange) * wanderPos.y;
		machineState->agentBase->SetWalkPoint(machineState->agentBase->getPosition() + wanderPos);
	}

	//Spot enemy, transition to Chase behaviour
	if (!Raycast::RaycastCollidesWall(machineState->agentBase->getPosition(), machineState->enemyAgent->getPosition(), machineState->maze))
	{
		std::cout << "--------------------------\n";
		std::cout << "SFM STATUS: CHASEBEHAVIOUR\n";
		std::cout << "EnemySpotted == true\n";
		if (machineState->enemyAgent->hasWeapon)
		{
			std::cout << "EnemyHasWeapon == true\n";
		}
		else
		{
			std::cout << "EnemyHasWeapon == false\n";
		}
		std::cout << "--------------------------\n";

		machineState->currBehaviour = new ChaseBehaviour(machineState);
		Exit();
		return;
	}

}

void WanderBehaviour::Exit()
{
	delete this;
}


