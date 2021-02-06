#pragma once
#include "Blackboard.h"

class STRIPS
{
public:
	Blackboard* blackboard;

	float cost = 0;
	float inc = 0.01f;

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

	virtual void Update(Agent* agent, Agent* enemy, Grid* maze) {};

	virtual void Init() { }

	virtual void Exit() { }

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
	bool arrived;
	std::stack<Node> path;

	ExploreSTRIPS() {
		cost = 0;

		arrived = false;

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

	void Update(Agent* agent, Grid* maze) {
		// Wander Behavior
		if (agent->getPathSize() == 0)
		{
			int n = 0; // ?
			Vector2D target = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
			while (!maze->isValidCell(target))
			{
				target = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
			}

			path = PathFinding::AStar(maze, maze->pix2cell(agent->getPosition()), target, n); // getTarget() no se si esta en modo pixel o en modo cell
			while (!path.empty()) {
				agent->addPathPoint(maze->cell2pix(path.top().GetPos()));
				path.pop();
			}
		}
	}

	void Init()
	{

	}

	void Exit()
	{

	}
};

class ApproachEnemySTRIPS : public STRIPS {
public:
	std::stack<Node> path;

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

	void Update(Agent* agent, Agent* enemy, Grid* maze) {
		// Chase Behavior
		int n = 0; // ?

		path = PathFinding::AStar(maze, maze->pix2cell(agent->getPosition()), maze->pix2cell(enemy->getPosition()), n);
		while (!path.empty()) {
			agent->addPathPoint(maze->cell2pix(path.top().GetPos()));
			path.pop();
		}
	}

	void Init()
	{

	}

	void Exit()
	{

	}
};

class AimSTRIPS : public STRIPS {
public:

	float counter;
	float time_aiming;

	AimSTRIPS() {
		cost = 0;

		counter = 0;
		time_aiming = 2.0f;

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
		
		counter += inc;
		
		if (counter >= time_aiming)
		{
			counter = 0;

			// Done
		}
	}

	void Init()
	{

	}

	void Exit()
	{

	}
};

class ShootSTRIPS : public STRIPS {
public:
	float counter;
	float time_shooting;

	ShootSTRIPS() {
		cost = 1;

		counter = 0;
		time_shooting = 1.0f;

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

		counter += inc;
		if (counter >= time_shooting)
		{
			counter = 0;

			// CHANGE BEHAVIOUR
		}
	}

	void Init()
	{

	}

	void Exit()
	{

	}
};

class ReloadWeaponSTRIPS : public STRIPS {
public:
	float counter;
	float time_reloading;

	ReloadWeaponSTRIPS() {
		cost = 2;

		counter = 0;
		time_reloading = 3.0f;

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

		counter += inc;
		if (counter >= time_reloading)
		{
			counter = 0;

			// CHANGE BEHAVIOUR
		}
	}

	void Init()
	{

	}

	void Exit()
	{

	}
};

class DetonateBombSTRIPS : public STRIPS {
public:
	float counter;
	float time_detonating;

	DetonateBombSTRIPS() {
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

	void Update(Agent* agent) {
		// Detonate Behaviour: player stops and detonates

		counter += inc;
		if (counter >= time_detonating)
		{
			counter = 0;

			// CHANGE BEHAVIOUR
		}
	}

	void Init()
	{

	}

	void Exit()
	{

	}
};

class RunAwaySTRIPS : public STRIPS {
public:
	std::stack<Node> path;

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

	void Update(Agent* agent, Grid* maze) {
		// Flee Behavior o Random target con A*?
		float dist, min_dist = 2;
		int n = 0;

		Vector2D target = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		dist = Vector2D::Distance(maze->pix2cell(agent->getPosition()), target);

		while (!maze->isValidCell(target) && dist > min_dist)
		{
			target = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
		}

		path = PathFinding::AStar(maze, maze->pix2cell(agent->getPosition()), target, n); // getTarget() no se si esta en modo pixel o en modo cell
		while (!path.empty()) {
			agent->addPathPoint(maze->cell2pix(path.top().GetPos()));
			path.pop();
		}
	}

	void Init()
	{

	}

	void Exit()
	{

	}
};

