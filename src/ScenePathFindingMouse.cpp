#include "ScenePathFindingMouse.h"

using namespace std;

double ScenePathFindingMouse::clamp(double x, double upper, double lower)
{
	if(x > upper)
	{
		return upper;
	}
	else if (x < lower)
	{
		return lower;
	}
	return x;
}

ScenePathFindingMouse::ScenePathFindingMouse()
{
	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	Agent *agent = new Agent;
	agent->setWorld(maze);
	agent->setMaxVelocity(200);
	agent->loadSpriteTexture("../res/soldier.png", 4);
	agent->setBehavior(new PathFollowing);
	agent->setTarget(Vector2D(-20,-20));
	agents.push_back(agent);

	
	for (int i = 0; i < TotalAgents; i++)
	{
		Enemy* agent = new Enemy();
		agent->Init(Vector2D(-20,-20));

		agent->setWorld(maze);
		agent->setMaxVelocity(200);
		agent->loadSpriteTexture("../res/soldier.png", 4);
		agent->setBehavior(new PathFollowing);
		agent->setTarget(Vector2D(-20, -20));
		actors.push_back(agent);
	}
	actors[0]->setPosition(maze->cell2pix(Vector2D(8, 8)));
	actors[1]->setPosition(maze->cell2pix(Vector2D(7, 7)));

	actors[0]->SetTargetEnemy(actors[1]);
	actors[0]->SetFiniteStateMachine();

	actors[1]->SetTargetEnemy(actors[0]);
	actors[1]->SetFiniteStateMachine();

	//Load zombie enemies(outdated)
	//enemy1.loadSpriteTexture("../res/zombie1.png", 8);
	//enemy1.setBehavior(new PathFollowing);
	//enemy1.setTarget(Vector2D(-20, -20));
	//enemy2.loadSpriteTexture("../res/zombie1.png", 8);
	//enemy2.setBehavior(new PathFollowing);
	//enemy2.setTarget(Vector2D(-20, -20));
	//enemy3.loadSpriteTexture("../res/zombie1.png", 8);
	//enemy3.setBehavior(new PathFollowing);
	//enemy3.setTarget(Vector2D(-20, -20));


	// set agent position coords to the center of a random cell
	Vector2D rand_cell(-1,-1);
	//while (!maze->isValidCell(rand_cell))
	//	rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	agents[0]->setPosition(maze->cell2pix(Vector2D(3, 3)));	//Todo: Canviar per rand_cell
	//enemy1.setPosition(maze->cell2pix(Vector2D(3, 18)));
	//enemy2.setPosition(maze->cell2pix(Vector2D(21, 3)));
	//enemy3.setPosition(maze->cell2pix(Vector2D(21, 18)));


	// set the coin in a random cell (but at least 3 cells far from the agent)
	coinPosition = Vector2D(-1,-1);
	while ((!maze->isValidCell(coinPosition)) || (Vector2D::Distance(coinPosition, rand_cell)<3))
		coinPosition = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

}

ScenePathFindingMouse::~ScenePathFindingMouse()
{
	if (background_texture)
		SDL_DestroyTexture(background_texture);
	if (coin_texture)
		SDL_DestroyTexture(coin_texture);

	for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}
}

void ScenePathFindingMouse::update(float dtime, SDL_Event *event)
{
	maze->resetTerrainModifiers();

	Vector2D target, start;
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;

		if (event->key.keysym.scancode == SDL_SCANCODE_RETURN) {
			// Do 20 paths
			start = maze->pix2cell(agents[0]->getPosition());

			system("CLS");

			while (actual_it < max_it)
			{
				actual_it++;
				do
				{
					target = Vector2D((float)(rand() % maze->getNumCellY()), (float)(rand() % maze->getNumCellX()));
				} while (!maze->isValidCell(target));

				PathFinding::AStar(maze, start, target, num);
				AStar_n.push_back(num);

				start = target;
			}

				// Minim i Maxim i Mitjana
				int min, max;
				float mitjana;

				min = *std::min_element(AStar_n.begin(), AStar_n.end());
				max = *std::max_element(AStar_n.begin(), AStar_n.end());
				mitjana = std::accumulate(AStar_n.begin(), AStar_n.end(), 0) / AStar_n.size();

				std::cout << "AStar:\n" << "Min - " << min << std::endl;
				std::cout << "Max - " << max << std::endl;
				std::cout << "Mitjana - " << mitjana << std::endl;
				std::cout << std::endl;
		}
		actual_it = 0;
		break;
	case SDL_MOUSEMOTION:
	case SDL_MOUSEBUTTONDOWN:
		if (event->button.button == SDL_BUTTON_LEFT)
		{
			//Pathfinding Algorithm here
			agents[0]->SetWalkPoint(Vector2D((float)(event->button.x), (float)(event->button.y)));
			/*
			targetCell = maze->pix2cell(Vector2D((float)(event->button.x), (float)(event->button.y)));
			if (maze->isValidCell(targetCell)) {
				if (agents[0]->getPathSize() > 0)
				{
					agents[0]->clearPath();
				}
				std::stack<Node> path;
				int n;
				path = PathFinding::AStar(maze, maze->pix2cell(agents[0]->getPosition()), targetCell, n);

				while (!path.empty()) {
					agents[0]->addPathPoint(maze->cell2pix(path.top().GetPos()));
					path.pop();
				}
			}
			*/

		}
		break;
	
	default:
		break;
	}

	//Update enemies
	UpdateEnemies(dtime, event);
	if (agents[0]->getPathSize() > 0)
		agents[0]->changeVelocityByNodeType(maze->GetNode(maze->pix2cell(agents[0]->getTarget())).GetType());
	//Update player
	agents[0]->update(dtime, event); 
	agents[0]->updatePath();

	for (Enemy* actor : actors)
	{
		actor->UpdateEnemy();
	}

}

void ScenePathFindingMouse::draw()
{
	drawMaze();
	drawCoin();

	int color = 255;

	if (draw_grid)
	{
		SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 255, 255, 255, 127);
		for (int i = 0; i < SRC_WIDTH; i+=CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), i, 0, i, SRC_HEIGHT);
		}
		for (int j = 0; j < SRC_HEIGHT; j = j += CELL_SIZE)
		{
			SDL_RenderDrawLine(TheApp::Instance()->getRenderer(), 0, j, SRC_WIDTH, j);
		}
	}

	agents[0]->draw(color, color, 0, color);

	for (Enemy* actor: actors)
	{
		actor->draw(color, color, 0, color);
	}
    
	//DEBUG FUNCTION, BORRAR CUANDO TERMINEMOS
	//for (auto it = maze->terrain_modifiers.begin(); it != maze->terrain_modifiers.end(); it++)
	//{
	//	draw_circle(TheApp::Instance()->getRenderer(), it->first.pos.x * 32 +11, it->first.pos.y * 32 + 11, 15, 255, 60, 0, 255);
	//}
}

const char* ScenePathFindingMouse::getTitle()
{
	return "SDL Path Finding :: PathFinding Mouse Demo";
}

void ScenePathFindingMouse::drawMaze()
{
	SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
	SDL_Rect rect;
	Vector2D coords;
	for (int j = 0; j < maze->getNumCellY(); j++)
	{
		for (int i = 0; i < maze->getNumCellX(); i++)
		{
			//Choose color
			switch (maze->GetType(Vector2D(i, j))) {
			case 0:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 255, 255);
				break;

			case 1:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 0, 0, 0);
				break;

			case 2:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 0, 255, 0, 255);
				break;

			case 3:
				SDL_SetRenderDrawColor(TheApp::Instance()->getRenderer(), 220, 0, 0, 255);
				break;

			default:;

			}

			coords = maze->cell2pix(Vector2D((float)i, (float)j)) - Vector2D((float)CELL_SIZE / 2, (float)CELL_SIZE / 2);
			rect = { (int)coords.x, (int)coords.y, CELL_SIZE, CELL_SIZE };
			SDL_RenderFillRect(TheApp::Instance()->getRenderer(), &rect);
			
		}
	}
	//Alternative: render a backgroud texture:
	//SDL_RenderCopy(TheApp::Instance()->getRenderer(), background_texture, NULL, NULL );
}

void ScenePathFindingMouse::drawCoin()
{
	Vector2D coin_coords = maze->cell2pix(coinPosition);
	int offset = CELL_SIZE / 2;
	SDL_Rect dstrect = {(int)coin_coords.x-offset, (int)coin_coords.y - offset, CELL_SIZE, CELL_SIZE};
	SDL_RenderCopy(TheApp::Instance()->getRenderer(), coin_texture, NULL, &dstrect);
}


bool ScenePathFindingMouse::loadTextures(char* filename_bg, char* filename_coin)
{
	SDL_Surface *image = IMG_Load(filename_bg);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	background_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	image = IMG_Load(filename_coin);
	if (!image) {
		cout << "IMG_Load: " << IMG_GetError() << endl;
		return false;
	}
	coin_texture = SDL_CreateTextureFromSurface(TheApp::Instance()->getRenderer(), image);

	if (image)
		SDL_FreeSurface(image);

	return true;
}

void ScenePathFindingMouse::UpdateEnemies(float dtime, SDL_Event * event)
{
	

	//enemy1.update(dtime, event); // BFS
	//enemy2.update(dtime, event); // Dijkstra
	//enemy3.update(dtime, event); // Greedy
	//
	//
	//
	//int n;
	//if (enemy1.getPathSize() == 0) {
	//	Vector2D newTarget(-1, -1);
	//	while (!maze->isValidCell(newTarget))
	//		newTarget = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	//
	//	std::stack<Node> path = PathFinding::BFS(maze, maze->pix2cell(enemy1.getPosition()), newTarget, n);
	//
	//	while (!path.empty()) {
	//		enemy1.addPathPoint(maze->cell2pix(path.top().GetPos()));
	//		path.pop();
	//	}
	//}
	//
	//if (enemy2.getPathSize() == 0) {
	//	Vector2D newTarget(-1, -1);
	//	while (!maze->isValidCell(newTarget))
	//		newTarget = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	//
	//	std::stack<Node> path = PathFinding::Dijkstra(maze, maze->pix2cell(enemy2.getPosition()), newTarget, n);
	//
	//	while (!path.empty()) {
	//		enemy2.addPathPoint(maze->cell2pix(path.top().GetPos()));
	//		path.pop();
	//	}
	//}
	//
	//if (enemy3.getPathSize() == 0) {
	//	Vector2D newTarget(-1, -1);
	//	while (!maze->isValidCell(newTarget))
	//		newTarget = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));
	//
	//	std::stack<Node> path = PathFinding::Greedy(maze, maze->pix2cell(enemy3.getPosition()), newTarget, n);
	//
	//	while (!path.empty()) {
	//		enemy3.addPathPoint(maze->cell2pix(path.top().GetPos()));
	//		path.pop();
	//	}
	//}
}
