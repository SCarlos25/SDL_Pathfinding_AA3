#pragma once
#include "Blackboard.h"

class STRIPS
{
public:
	Blackboard *blackboard;

	std::unordered_map<std::string, bool> conditions;
	std::unordered_map<std::string, bool> effects;

	STRIPS() {}

	bool ConditionsAccomplished() {
		for (auto it = conditions.begin(); it != conditions.end(); it++) {
			if (it->second != blackboard->conditions[it->first])
				return false;
		}

		return true;
	}

	// Explorar
	//	cond: isAlive, tal...

	// Apropar-se a Enemic

	// Apuntar

	// Disparar

	// Carregar Arma

	// Detonar Bomba

	// Fugir de l'Enemic

};

class ExploreSTRIPS : public STRIPS {
	ExploreSTRIPS() {
		// Init Conditions
		conditions.insert(std::make_pair("agentAlive", true));
		conditions.insert(std::make_pair("enemyVisible", false));
		conditions.insert(std::make_pair("enemyNearby", false));
		conditions.insert(std::make_pair("enemyAlive", true));

		// Init Effects
		// ...
	}


};