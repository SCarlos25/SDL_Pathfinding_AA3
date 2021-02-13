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
	enum class STRIPSTypes { EXPLORE = 0, APPROACH_ENEMY, AIM, DETONATE, RELOAD, RUN_AWAY, SHOOT, NONE };
	STRIPSTypes type = STRIPSTypes::NONE;

	//std::string id = "";
	float cost = 0;
	float inc = 0.01f;

	std::unordered_map<std::string, bool> conditions;
	std::unordered_map<std::string, bool> effects;
	std::queue<STRIPS*> neighbours;
	//STRIPS* cameFrom = nullptr;
	//float costSoFar = -1;

public:
	STRIPS() {};

	bool ConditionsAccomplished(std::unordered_map<std::string, bool>& currConditions);

	bool EffectsAccomplished(std::unordered_map<std::string, bool>& currConditions);

	void TriggerEffects(std::unordered_map<std::string, bool>& currConditions);

	/*std::unordered_map<std::string, bool> GetNewConditions(std::unordered_map<std::string, bool> currConditions) {
		for (auto it = effects.begin(); it != effects.end(); it++) {
			currConditions[it->first] = it->second;
		}

		return currConditions;
	}*/

	virtual void Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* _blackboard) {};

	virtual void Init() { }

	virtual void Exit();

	friend bool operator==(STRIPS s1, STRIPS s2)
	{
		return s1.type == s2.type;
	}
	friend bool operator!=(STRIPS s1, STRIPS s2)
	{
		return s1.type != s2.type;
	}

	virtual std::queue<STRIPS*> GetNeighbours()
	{
		return std::queue<STRIPS*>();
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


namespace std {

	template <>
	struct hash<STRIPS>
	{
		std::size_t operator()(const STRIPS& k) const
		{
			using std::size_t;
			using std::hash;
			using std::string;

			// Compute individual hash values for first,
			// second and third and combine them using XOR
			// and bit shifting:

			return /*((hash<int>()((int)k.neighbours.back()->type)
				^ (hash<int>()((int)k.neighbours.front()->type) << 1)) >> 1)
				^ */(hash<int>()((int)k.type) << 1);
		}
	};

}

