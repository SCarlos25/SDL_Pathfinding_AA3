#pragma once
#include "Blackboard.h"

/*#include	"ShootSTRIPS.h"
#include	"RunAwaySTRIPS.h"
#include	"ReloadWeaponSTRIPS.h"
#include	"ExploreSTRIPS.h"
#include	"DetonateBombSTRIPS.h"
#include	"ApproachSTRIPS.h"
#include	"AimSTRIPS.h"*/


class STRIPS
{
public:
	//Blackboard* blackboard;
	std::string id = "";

	float cost = 0;
	float inc = 0.01f;

	std::unordered_map<std::string, bool> conditions;
	std::unordered_map<std::string, bool> effects;
	std::queue<STRIPS*> neighbours;
	STRIPS* cameFrom = nullptr;
	float costSoFar = -1;

public:
	STRIPS() {};

	bool ConditionsAccomplished(std::unordered_map<std::string, bool>& currConditions);

	void TriggerEffects(std::unordered_map<std::string, bool>& currConditions);

	/*std::unordered_map<std::string, bool> GetNewConditions(std::unordered_map<std::string, bool> currConditions) {
		for (auto it = effects.begin(); it != effects.end(); it++) {
			currConditions[it->first] = it->second;
		}

		return currConditions;
	}*/

	virtual void Update(Agent* agent, Agent* enemy, Grid* maze) {};

	virtual void Init() { }

	virtual void Exit() { }

	friend bool operator==(STRIPS s1, STRIPS s2)
	{
		return s1.id == s2.id;
	}
	friend bool operator!=(STRIPS s1, STRIPS s2)
	{
		return s1.id != s2.id;
	}

	#pragma region Notas
	// Para todas las acciones: agentAlive == true

	// EXPLORAR
	//	cond: !enemyNearby, !enemyVisible

	// APROPAR-SE A L'ENEMIC
	//	cond: !enemyNearby, enemyVisible <-- se hace con un raycast a todos los enemigos
	//	ef: enemyNearby

	// APUNTAR
	//  cond: hasWeapon, enemyNearby, enemyVisible, !aiming
	//  ef: aiming

	// DISPARAR
	// cond: hasWeapon, enemyNearby, enemyVisible, loadedWeapon, aiming
	// ef: !hasWeapon

	// CARREGAR ARMA
	//  cond: hasWeapon, !loadedWeapon, aiming
	// ef: loadedWeapon

	// DETONAR BOMBA
	//  cond: hasBomb
	//  ef: !hasBomb

	// FUGIR DE L'ENEMIC
	//  cond: !enemyHasGun?
#pragma endregion

};

