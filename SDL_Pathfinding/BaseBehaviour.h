#pragma once
#include "../src/Vector2D.h"

class FiniteStateMachine;

class BaseBehaviour
{
public:
	FiniteStateMachine *machineState;
	
	BaseBehaviour() 
	{

	}
	
	virtual void Init() { return; }
	
	virtual void Update(){return;}
	
	virtual void Exit() { return; }
};
