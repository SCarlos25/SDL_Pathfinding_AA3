#pragma once
class FiniteStateMachine;

class BaseBehaviour
{
public:
	FiniteStateMachine *machineState;

	BaseBehaviour() 
	{

	}
	
	void Init();
	
	virtual void Update();
	
	void Exit();
};
