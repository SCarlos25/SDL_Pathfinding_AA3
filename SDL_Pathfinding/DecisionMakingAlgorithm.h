#pragma once
class Enemy;
class Grid;
class STRIPS;
class Blackboard;

class DecisionMakingAlgorithm
{
public:
	Enemy* agentBase;
	Enemy* enemyAgent;
	Grid* maze;
	Blackboard* blackboard;

	virtual void Init(Enemy* _allyAgent, Enemy* _enemyAgent, Grid* maze, Blackboard* _blackboard) { return; }

	virtual void Update() { return; }

	virtual void ChangeStrips(/*STRIPS* change*/) {};

};