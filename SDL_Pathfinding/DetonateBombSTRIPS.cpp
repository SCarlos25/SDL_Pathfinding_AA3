#include "DetonateBombSTRIPS.h"
#include "ExploreSTRIPS.h"
#include "ApproachSTRIPS.h"
#include "RunAwaySTRIPS.h"

DetonateBombSTRIPS::DetonateBombSTRIPS(bool initNeighbours = true) {
	type = STRIPSTypes::DETONATE;
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
	neighbours.push(new ExploreSTRIPS(false));
	neighbours.push(new ApproachEnemySTRIPS(false));
	neighbours.push(new RunAwaySTRIPS(false));
}

void DetonateBombSTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze) {
	// Detonate Behaviour: player stops and detonates

	if (counter >= time_detonating)
	{
		counter = 0;

		// CHANGE BEHAVIOUR
	}
}