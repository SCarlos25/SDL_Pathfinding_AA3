#include "Blackboard.h"
#include "Priority_STRIPS.h"
#include "Enemy.h"
#include "Ally.h"
#include "Raycast.h"

//Blackboard* Blackboard::GetInstance() 

Blackboard::Blackboard()
{
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("hasWeapon", true));
	conditions.insert(std::make_pair("loadedWeapon", true));
	conditions.insert(std::make_pair("hasBomb", true));

	conditions.insert(std::make_pair("enemyVisible", false));
	//conditions.insert(std::make_pair("enemyAligned", false));
	conditions.insert(std::make_pair("enemyNearby", false));
	conditions.insert(std::make_pair("enemyAlive", true));
	conditions.insert(std::make_pair("enemyHasWeapon", false));
	conditions.insert(std::make_pair("enemyHasBomb", false));
}

void Blackboard::UpdateConditionsState(Enemy* ally, Enemy* enemy, Grid *maze)
{
	conditions["agentAlive"] = ally->alive;
	conditions["hasWeapon"] = ally->hasWeapon;
	conditions["loadedWeapon"] = ally->loadedWeapon;
	conditions["hasBomb"] = ally->hasBomb;
	
	conditions["enemyVisible"] = Raycast::RaycastCollidesWall(ally->getPosition(), enemy->getPosition(), maze);
	conditions["enemyNearby"] = Vector2D::DistanceSquared(ally->getPosition(), enemy->getPosition()) < AGENT_RANGE;
	conditions["enemyAlive"] = enemy->alive;
	conditions["enemyHasWeapon"] = enemy->hasWeapon;
	conditions["enemyHasBomb"] = enemy->hasBomb;
}

// TODO: 


