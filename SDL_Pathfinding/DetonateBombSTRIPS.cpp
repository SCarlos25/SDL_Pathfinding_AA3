#include "DetonateBombSTRIPS.h"

DetonateBombSTRIPS::DetonateBombSTRIPS() {
	cost = 2;

	counter = 0;
	time_detonating = 2.0f;

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

void DetonateBombSTRIPS::Update(Agent* agent) {
	// Detonate Behaviour: player stops and detonates

	counter += inc;
	if (counter >= time_detonating)
	{
		counter = 0;

		// CHANGE BEHAVIOUR
	}
}