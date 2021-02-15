#pragma once
#include <iostream>
#include <SDL.h>


class Scene
{
public:
	static float deltaTime;
	static bool pause;

	Scene() {};
	virtual ~Scene() {};
	virtual void update(float dtime, SDL_Event *event) = 0;
	virtual void draw() = 0;
	virtual const char* getTitle() { return ""; };
	virtual bool gameOver() { return false; }
	//static float getDeltaTime() { return deltaTime; }
	//static void setDeltaTime(float gDTime) { deltaTime = gDTime; }
};
