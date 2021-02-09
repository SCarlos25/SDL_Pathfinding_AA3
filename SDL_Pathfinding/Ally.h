#pragma once
#include "../src/Agent.h"
#include "GOAP.h"


class Ally : public Agent // Agente aqui da error
{
public:
	GOAP* goapState;

	Ally();

	void Init(Vector2D pos);

	void SetFiniteStateMachine();

	void Update();

};

