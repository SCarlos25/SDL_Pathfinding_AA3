#include "Chase_Behaviour.h"
#include "Wander_Behaviour.h"
#include "Flee_Behaviour.h"
#include "Raycast.h"
#include "FiniteStateMachine.h"
#include "../SDL_Pathfinding/Enemy.h"
#include "../src/ScenePathFindingMouse.h"
#include "../src/utils.h"

void ChaseBehaviour::Init()
{

}

void ChaseBehaviour::Update()
{
	//If we lose vision with our target go back to wandering
	if (Raycast::RaycastCollidesWall(machineState->agentBase->getPosition(), machineState->enemyAgent->getPosition(), machineState->maze))
	{
		machineState->currBehaviour = new WanderBehaviour(machineState);
		machineState->agentBase->clearPath();
		Exit();
		return;
	}

	//If the target has a weapon then start RUNNING
	if (machineState->enemyAgent->hasWeapon)
	{
		machineState->currBehaviour = new FleeBehaviour(machineState);
		machineState->agentBase->clearPath();
		Exit();
		return;
	}

	//If we dont lose vision we are seeing the target, if the target's position doesn't mark our current position 
	//then recalculate chase target
	if (machineState->agentBase->getTarget() != machineState->enemyAgent->getPosition())
	{
		machineState->agentBase->SetWalkPoint(machineState->enemyAgent->getPosition());
	}

}

void ChaseBehaviour::Exit()
{
	delete this;
}