#include "Agent.h"
//Include map stuff
#include "PathFinding.h"
#include "../SDL_Pathfinding/Priority_STRIPS.h"

using namespace std;

double clamp(double x, double upper, double lower)
{
	return min(upper, max(x, lower));
}

Agent::Agent() : sprite_texture(0),
                 position(Vector2D(100, 100)),
	             target(Vector2D(1000, 100)),
	             velocity(Vector2D(0,0)),
	             currentTargetIndex(-1),
				 mass(0.1f),
				 max_force(150),
				 max_velocity(70),
				 orientation(0),
				 sprite_num_frames(0),
	             sprite_w(0),
	             sprite_h(0),
	             draw_sprite(false),
				 velocity_normal(200),
				 velocity_speed(400)
{
}

Agent::~Agent()
{
	if (sprite_texture)
		SDL_DestroyTexture(sprite_texture);
	if (steering_behaviour)
		delete (steering_behaviour);
}

void Agent::setBehavior(SteeringBehavior* behavior)
{
	steering_behaviour = behavior;
}

Vector2D Agent::getPosition()
{
	return position;
}

Vector2D Agent::getTarget()
{
	return target;
}

Vector2D Agent::getVelocity()
{
	return velocity;
}

float Agent::getMaxVelocity()
{
	return max_velocity;
}

float Agent::getMaxForce()
{
	return max_force;
}

float Agent::getMass()
{
	return mass;
}

void Agent::setWorld(Grid *gWorld)
{
	maze = gWorld;
}

void Agent::setPosition(Vector2D _position)
{
	position = _position;
}

void Agent::setTarget(Vector2D _target)
{
	target = _target;
}

void Agent::setVelocity(Vector2D _velocity)
{
	velocity = _velocity;
}


void Agent::update(float dtime, SDL_Event *event)
{
	if (getPathSize() > 0)
		changeVelocityByNodeType(maze->GetNode(maze->pix2cell(getTarget())).GetType());
	//cout << "agent update:" << endl;

	/*
	switch (event->type) {
		//Keyboard & Mouse events 
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_sprite = !draw_sprite;
		break;
	default:
		break;
	}
	*/

	// Apply the steering behavior
	steering_behaviour->applySteeringForce(this, dtime);

	// Update orientation
	if (velocity.Length())
		orientation = (float)(atan2(velocity.y, velocity.x) * RAD2DEG);

	// Trim position values to window size
	if (position.x < 0) position.x = TheApp::Instance()->getWinSize().x;
	if (position.y < 0) position.y = TheApp::Instance()->getWinSize().y;
	if (position.x > TheApp::Instance()->getWinSize().x) position.x = 0;
	if (position.y > TheApp::Instance()->getWinSize().y) position.y = 0;
}

void Agent::updatePath()
{
	int currentTargetIndex = getCurrentTargetIndex(); if (currentTargetIndex < 0) { currentTargetIndex = 0; }
	int futTarget = clamp(currentTargetIndex + ((getPathSize() - currentTargetIndex) / 2), getPathSize(), currentTargetIndex);
	if (futTarget > getPathSize())
	{
		futTarget = getPathSize();
	}
	for (int i = currentTargetIndex; i < futTarget; i++)
	{
		if (i >= getPathSize())
		{
			i = futTarget;
			int e = getPathSize();
		}
		if (maze->terrain_modifiers.find(maze->GetNode(maze->pix2cell(getPathPoint(i)))) != maze->terrain_modifiers.end())
		{
			clearPath();
			std::stack<Node> path;
			int n;
			path = PathFinding::AStar(maze, maze->pix2cell(getPosition()), target, n);

			while (!path.empty()) {
				addPathPoint(maze->cell2pix(path.top().GetPos()));
				path.pop();
			}
			i = futTarget;
		}
	}
}

void Agent::SetWalkPoint(Vector2D point)
{
	target = point;
	Vector2D targetCell = maze->pix2cell(Vector2D((float)(point.x), (float)(point.y)));
	if (maze->isValidCell(targetCell)) {
		if (getPathSize() > 0)
		{
			clearPath();
		}
		std::stack<Node> path;
		int n;
		path = PathFinding::AStar(maze, maze->pix2cell(getPosition()), targetCell, n);

		while (!path.empty()) {
			addPathPoint(maze->cell2pix(path.top().GetPos()));
			path.pop();
		}
	}
}

void Agent::addPathPoint(Vector2D point)
{
	if (path.points.size() > 0)
		if (path.points[path.points.size() - 1] == point)
			return;

	path.points.push_back(point);
}


int Agent::getCurrentTargetIndex()
{
	return currentTargetIndex;
}

int Agent::getPathSize()
{
	return path.points.size();
}

Vector2D Agent::getPathPoint(int idx)
{
	return path.points[idx];
}

void Agent::clearPath()
{
	setCurrentTargetIndex(-1);
	path.points.clear();
}

void Agent::setCurrentTargetIndex(int idx)
{
	currentTargetIndex = idx;
}

void Agent::draw(int _r, int _g, int _b, int _h)
{
	// Path
	for (int i = 0; i < (int)path.points.size(); i++)
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)(path.points[i].x), (int)(path.points[i].y), 15, _r, _g, _b, _h);
		if (i > 0)
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)(path.points[i - 1].x), (int)(path.points[i - 1].y), (int)(path.points[i].x), (int)(path.points[i].y));
	}

	if (draw_sprite)
	{
		Uint32 sprite;

		if (velocity.Length() < 5.0)
			sprite = 1;
		else
			sprite = (int)(SDL_GetTicks() / (-0.1*velocity.Length() + 250)) % sprite_num_frames;

		SDL_Rect srcrect = { (int)sprite * sprite_w, 0, sprite_w, sprite_h };
		SDL_Rect dstrect = { (int)position.x - (sprite_w / 2), (int)position.y - (sprite_h / 2), sprite_w, sprite_h };
		SDL_Point center = { sprite_w / 2, sprite_h / 2 };
		SDL_RenderCopyEx(TheApp::Instance()->getRenderer(), sprite_texture, &srcrect, &dstrect, orientation+90, &center, SDL_FLIP_NONE);
	}
	else
	{
		draw_circle(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, 15, 255, 255, 255, 255);
		SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), (int)position.x, (int)position.y, (int)(position.x+15*cos(orientation*DEG2RAD)), (int)(position.y+15*sin(orientation*DEG2RAD)));
	}


}

bool Agent::loadSpriteTexture(char* filename, int _num_frames)
{
	if (_num_frames < 1) return false;

	SDL_Surface *image = IMG_Load(filename);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	sprite_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	sprite_num_frames = _num_frames;
	sprite_w = image->w / sprite_num_frames;
	sprite_h = image->h;
	draw_sprite = true;

	if (image)
		SDL_FreeSurface(image);

	return true;
}

void Agent::setMaxVelocity(float newVelocity)
{
	max_velocity = newVelocity;
}

void Agent::changeVelocityByNodeType(int type)
{
	switch (type)
	{
	case 1:
		setMaxVelocity(velocity_normal);
		break;

	case 2:
		setMaxVelocity(velocity_speed);
		break;

	case 3:
		setMaxVelocity(100);
		break;

	default:
		setMaxVelocity(200);
		break;
	}
}
