#pragma once
class Enemy{};
class FiniteStateMachine{};

class BaseBehaviour
{
public:
	BaseBehaviour();

	virtual void Init();

	virtual void Update();

	virtual void Exit();
};
