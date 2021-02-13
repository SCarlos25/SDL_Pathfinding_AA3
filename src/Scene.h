#pragma once
#include <iostream>
#include <SDL.h>


class Scene
{
public:
	static float deltaTime;

	Scene() {};
	virtual ~Scene() {};
	virtual void update(float dtime, SDL_Event *event) = 0;
	virtual void draw() = 0;
	virtual const char* getTitle() { return ""; };
	//static float getDeltaTime() { return deltaTime; }
	//static void setDeltaTime(float gDTime) { deltaTime = gDTime; }
};
