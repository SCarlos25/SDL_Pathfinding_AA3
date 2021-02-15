#include "DetonateBombSTRIPS.h"
#include "ExploreSTRIPS.h"
#include "ApproachSTRIPS.h"
#include "RunAwaySTRIPS.h"

DetonateBombSTRIPS::DetonateBombSTRIPS() {
	type = STRIPSTypes::DETONATE;
	cost = 2;
	name = "Detonate";

	counter = 0;
	time_detonating = 2.0f;

	// Init Conditions
	conditions.insert(std::make_pair("agentAlive", true));
	conditions.insert(std::make_pair("hasBomb", true));

	// Init Effects
	effects.insert(std::make_pair("hasBomb", false));
	effects.insert(std::make_pair("enemyAlive", false));

}

void DetonateBombSTRIPS::Update(Enemy* agent, Enemy* enemy, Grid* maze, Blackboard* blackboard) {
	// Detonate Behaviour: player stops and detonates

	if (counter >= time_detonating)
	{
		counter = 0;

		// CHANGE BEHAVIOUR
	}
}

std::queue<STRIPS*> DetonateBombSTRIPS::GetNeighbours()
{
	std::queue<STRIPS*> n;
	n.push(new ExploreSTRIPS());
	n.push(new ApproachEnemySTRIPS());
	n.push(new RunAwaySTRIPS());

	return n;
}