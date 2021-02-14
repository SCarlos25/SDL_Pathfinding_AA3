#include "Flee_Behaviour.h"
#include "Wander_Behaviour.h"
#include "Chase_Behaviour.h"
#include "Raycast.h"
#include "FiniteStateMachine.h"
#include "../SDL_Pathfinding/Enemy.h"
#include "../src/ScenePathFindingMouse.h"
#include "../src/utils.h"

void FleeBehaviour::Init()
{

}

void FleeBehaviour::Update()
{
	//If we lose vision with the enemy go back to wanderbehaviour
	if (Raycast::RaycastCollidesWall(machineState->agentBase->getPosition(), machineState->enemyAgent->getPosition(), machineState->maze))
	{
		machineState->currBehaviour = new WanderBehaviour(machineState);
		Exit();
		return;
	}

	//If our chaser has no gun, then go back to chasing him instead!
	if (!machineState->enemyAgent->hasWeapon)
	{
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



	/*
	if (machineState->agentBase->getTarget() != machineState->enemyAgent->getPosition() &&
		!RaycastCollidesWall(machineState->agentBase->getPosition(), machineState->enemyAgent->getPosition(), machineState->maze))
	{
		if (!machineState->enemyAgent->hasGun)
		{
			machineState->agentBase->SetWalkPoint(machineState->enemyAgent->getPosition());
		}
		else if (machineState->agentBase->getPathSize() == 0)
		{
			Vector2D wanderPos = machineState->agentBase->getPosition();
			wanderPos.x = RandomNumber(-1, 1);
			wanderPos.y = RandomNumber(-1, 1);
			wanderPos.x = RandomNumber(140, 260) * wanderPos.x;
			wanderPos.y = RandomNumber(140, 260) * wanderPos.y;
			machineState->agentBase->SetWalkPoint(machineState->agentBase->getPosition() + wanderPos);
		}
	}
	*/
}

void FleeBehaviour::Exit()
{
	delete this;
}