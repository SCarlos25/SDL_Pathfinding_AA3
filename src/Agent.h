#pragma once
#include <iostream>
#include <minmax.h>
#include <SDL.h>
#include <SDL_image.h>
#include <stack>
#include <algorithm>
#include "SDL_SimpleApp.h"
#include "Path.h"
#include "Vector2D.h"
#include "utils.h"

#include "../SDL_Pathfinding/DecisionMakingAlgorithm.h"
//#include "../SDL_Pathfinding/STRIPS.h"

//Forward declarations
class PathFinding;
class Grid;
class STRIPS;

class Agent
{
public:
	static int agentID;

	class SteeringBehavior
	{
	public:
		SteeringBehavior() {};
		virtual ~SteeringBehavior() {};
		virtual void applySteeringForce(Agent *agent, float dtime) {};

		DecisionMakingAlgorithm *my_algorithm; // Inicializar hace petar
	};

	private:

	SteeringBehavior *steering_behaviour;
	Vector2D position;
	Vector2D velocity;
	Vector2D target;

	// Pathfinding
	Path path;
	int currentTargetIndex;

	float mass;
	float orientation;
	float max_force;
	float max_velocity;

	SDL_Texture *sprite_texture;
	bool draw_sprite;
	int sprite_num_frames;
	int sprite_w;
	int sprite_h;

public:
	float velocity_normal;
	float velocity_speed;
	bool alive = true;
	bool hasWeapon = false;
	bool loadedWeapon = false;
	bool hasBomb = false;
	//Referencia al mapa
	Grid* maze;

	Agent();
	~Agent();
	Vector2D getPosition();
	Vector2D getTarget();
	Vector2D getVelocity();
	float getMaxVelocity();
	float getMaxForce();
	float getMass();
	void setWorld(Grid* gWorld);
	void setBehavior(SteeringBehavior *behavior);
	void setPosition(Vector2D position);
	void setTarget(Vector2D target);
	void setVelocity(Vector2D velocity);
	void SetWalkPoint(Vector2D point);
	void addPathPoint(Vector2D point);
	void setCurrentTargetIndex(int idx);
	int getCurrentTargetIndex();
	int getPathSize();
	Vector2D getPathPoint(int idx);
	void clearPath();
	void update(float dtime, SDL_Event *event);
	void updatePath();
	void draw(int _r, int _g, int _b, int _h);
	bool Agent::loadSpriteTexture(char* filename, int num_frames=1);
	void setMaxVelocity(float newVelocity);
	void changeVelocityByNodeType(int type);
	bool validPoint(Vector2D);
	
};
