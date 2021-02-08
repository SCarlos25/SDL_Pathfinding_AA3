#pragma once
#include "Vector2D.h"

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
