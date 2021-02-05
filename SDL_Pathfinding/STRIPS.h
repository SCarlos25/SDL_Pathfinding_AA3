#pragma once
#include "Blackboard.h"

class STRIPS
{
public:
	Blackboard* blackboard;

	float cost = 0;

	std::unordered_map<std::string, bool> conditions;
	std::unordered_map<std::string, bool> effects;
	std::queue<STRIPS*> neighbours;
	STRIPS* cameFrom = nullptr;
	float costSoFar = -1;

public:
	STRIPS() {}

	bool ConditionsAccomplished(std::unordered_map<std::string, bool>& currConditions) {
		for (auto it = conditions.begin(); it != conditions.end(); it++) {
			if (it->second != currConditions[it->first])
				return false;
		}

		/*for (auto it = conditions.begin(); it != conditions.end(); it++) {
			if (it->second != blackboard->conditions[it->first])
				return false;
		}*/

		return true;
	}

	void TriggerEffects(std::unordered_map<std::string, bool>& currConditions) {
		for (auto it = effects.begin(); it != effects.end(); it++) {
			currConditions[it->first] = it->second;
		}

		/*for (auto it = effects.begin(); it != effects.end(); it++) {
			blackboard->conditions[it->first] = it->second;
		}*/
	}

	/*std::unordered_map<std::string, bool> GetNewConditions(std::unordered_map<std::string, bool> currConditions) {
		for (auto it = effects.begin(); it != effects.end(); it++) {
			currConditions[it->first] = it->second;
		}

		return currConditions;
	}*/

	virtual void Update(Agent* agent) {};

	friend bool operator==(STRIPS s1, STRIPS s2) {

		return s1.conditions == s2.conditions && s1.effects == s2.effects && s1.neighbours == s2.neighbours;
	}
	friend bool operator!=(STRIPS s1, STRIPS s2) {

		return (s1.conditions == s2.conditions && s1.effects == s2.effects && s1.neighbours == s2.neighbours);
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

class ExploreSTRIPS : public STRIPS {
public:
	ExploreSTRIPS() {
		cost = 0;

		// Init Conditions
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("enemyVisible", false));
		conditions.insert(std::make_pair("enemyNearby", false));

		// Init Effects
		// ...

		// Init neighbors
		neighbours = std::queue<STRIPS*>();
		neighbours.push(new ApproachEnemySTRIPS());
		neighbours.push(new DetonateBombSTRIPS());
	}

	void Update(Agent* agent) {
		// Wander Behavior
	}
};

class ApproachEnemySTRIPS : public STRIPS {
public:
	ApproachEnemySTRIPS() {
		cost = 1;

		// Init Conditions
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("enemyVisible", false));
		conditions.insert(std::make_pair("enemyNearby", false));
		conditions.insert(std::make_pair("enemyAlive", true));
		conditions.insert(std::make_pair("enemyHasGun", false));

		// Init Effects
		effects.insert(std::make_pair("enemyNearby", true));

		// Init neighbors
		neighbours = std::queue<STRIPS*>();
		neighbours.push(new AimSTRIPS());
		neighbours.push(new ExploreSTRIPS());
		neighbours.push(new RunAwaySTRIPS());
		neighbours.push(new DetonateBombSTRIPS());
	}

	void Update(Agent* agent) {
		// Chase Behavior
	}
};

class AimSTRIPS : public STRIPS {
public:
	AimSTRIPS() {
		cost = 0;

		// Init Conditions
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("enemyVisible", false));
		conditions.insert(std::make_pair("enemyNearby", false));
		conditions.insert(std::make_pair("enemyAlive", true));
		conditions.insert(std::make_pair("enemyHasGun", false));
		conditions.insert(std::make_pair("hasWeapon", true));
		conditions.insert(std::make_pair("aiming", false));
		conditions.insert(std::make_pair("loadedWeapon", true));

		// Init Effects
		effects.insert(std::make_pair("aiming", true));

		// Init neighbors
		neighbours = std::queue<STRIPS*>();
		neighbours.push(new ShootSTRIPS());
		neighbours.push(new ReloadWeaponSTRIPS());
	}

	void Update(Agent* agent) {
		// Aim Behavior: wait a second and, if still on range, change to ShootSTRIPS
	}
};

class ShootSTRIPS : public STRIPS {
public:
	ShootSTRIPS() {
		cost = 1;

		// Init Conditions
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("enemyVisible", false));
		conditions.insert(std::make_pair("enemyNearby", false));
		conditions.insert(std::make_pair("enemyAlive", true));
		conditions.insert(std::make_pair("enemyHasGun", false));
		conditions.insert(std::make_pair("hasWeapon", true));
		conditions.insert(std::make_pair("aiming", true));
		conditions.insert(std::make_pair("loadedWeapon", true));

		// Init Effects
		effects.insert(std::make_pair("loadedWeapon", false));
		effects.insert(std::make_pair("enemyAlive", false));

		// Init neighbors
		neighbours = std::queue<STRIPS*>();
		neighbours.push(new ApproachEnemySTRIPS());
		neighbours.push(new ExploreSTRIPS());
		neighbours.push(new RunAwaySTRIPS());
		neighbours.push(new AimSTRIPS()); //?
	}

	void Update(Agent* agent) {
		// Shoot Behavior: kills target agent
	}
};

class ReloadWeaponSTRIPS : public STRIPS {
public:
	ReloadWeaponSTRIPS() {
		cost = 2;

		// Init Conditions
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("hasWeapon", true));
		conditions.insert(std::make_pair("loadedWeapon", false));
		conditions.insert(std::make_pair("aiming", true));
		conditions.insert(std::make_pair("enemyHasGun", false));

		// Init Effects
		effects.insert(std::make_pair("loadedWeapon", true));

		// Init neighbors
		neighbours = std::queue<STRIPS*>();
		neighbours.push(new AimSTRIPS());
		neighbours.push(new RunAwaySTRIPS());
		neighbours.push(new ApproachEnemySTRIPS());
	}

	void Update(Agent* agent) {
		// Reload Behaviour: wait a second still and end behaviour
	}
};

class DetonateBombSTRIPS : public STRIPS {
public:
	DetonateBombSTRIPS() {
		cost = 2;

		// Init Conditions
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("hasBomb", true));

		// Init Effects
		effects.insert(std::make_pair("hasBomb", false));
		effects.insert(std::make_pair("enemyAlive", false));

		// Init neighbors
		neighbours = std::queue<STRIPS*>();
		neighbours.push(new ExploreSTRIPS());
		neighbours.push(new ApproachEnemySTRIPS());
		neighbours.push(new RunAwaySTRIPS());
	}

	void Update(Agent* agent) {
		// Detonate Behaviour: player stops and detonates
	}
};

class RunAwaySTRIPS : public STRIPS {
public:
	RunAwaySTRIPS() {
		cost = 1;

		// Init Conditions
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("enemyAlive", true));
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("enemyHasGun", true));
		conditions.insert(std::make_pair("hasWeapon", false));

		// Init Effects
		effects.insert(std::make_pair("enemyNearby", false));
		effects.insert(std::make_pair("enemyVisible", false));

		// Init neighbors
		neighbours = std::queue<STRIPS*>();
		neighbours.push(new ExploreSTRIPS());
		neighbours.push(new ApproachEnemySTRIPS());
	}

	void Update(Agent* agent) {
		// Flee Behavior

		// resetar condiciones
	}
};

