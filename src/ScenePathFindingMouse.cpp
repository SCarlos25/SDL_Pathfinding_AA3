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
	blackboard = new Blackboard();

	draw_grid = false;
	maze = new Grid("../res/maze.csv");

	loadTextures("../res/maze.png", "../res/coin.png");

	srand((unsigned int)time(NULL));

	//Agent *agent = new Agent;
	//agent->setWorld(maze);
	//agent->setMaxVelocity(200);
	//agent->loadSpriteTexture("../res/soldier.png", 4);
	//agent->setBehavior(new PathFollowing);
	//agent->setTarget(Vector2D(-20,-20));
	//agents.push_back(agent);

	GOAP_Algorithm = new GOAP;
	DM_Algorithm = new DecisionMakingAlgorithm;

	FSM_Agent = new Enemy;
	GOAP_Agent = new Enemy;

	GOAP_Agent->setWorld(maze);
	GOAP_Agent->setMaxVelocity(200);
	GOAP_Agent->loadSpriteTexture("../res/soldier.png", 4);
	GOAP_Agent->setTarget(Vector2D(-20, -20));

	FSM_Agent->setWorld(maze);
	FSM_Agent->setMaxVelocity(200);
	FSM_Agent->loadSpriteTexture("../res/zombie1.png", 8);
	FSM_Agent->setTarget(Vector2D(-20, -20));

	FSM_Agent->SetTargetEnemy(GOAP_Agent);
	FSM_Agent->SetFiniteStateMachine(blackboard);
	FSM_Agent->GiveGun();


	GOAP_Algorithm->Init(GOAP_Agent, FSM_Agent, maze, blackboard);
	//DM_Algorithm->Init(FSM_Agent, GOAP_Agent, maze, blackboard);

	GOAP_Agent->currAlgorithm = GOAP_Algorithm;
	//FSM_Agent->currAlgorithm = DM_Algorithm;

	GOAP_Agent->targetEnemy = FSM_Agent;
	//FSM_Agent->targetEnemy = GOAP_Agent;

	//FSM_Agent->hasWeapon = true;
	GOAP_Agent->hasWeapon = true;

	FSM_Agent->setBehavior(new PathFollowing);
	GOAP_Agent->setBehavior(new PathFollowing);

	
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

	/*actors[0]->setPosition(maze->cell2pix(Vector2D(24, 8)));
	actors[1]->setPosition(maze->cell2pix(Vector2D(7, 7)));

	actors[0]->velocity_normal = 160;
	actors[0]->velocity_speed = 360;
	actors[0]->SetTargetEnemy(actors[1]);
	actors[0]->SetFiniteStateMachine(blackboard);
	actors[0]->GiveGun();

	actors[1]->velocity_normal = 250;
	actors[1]->velocity_speed = 450;
	actors[1]->SetTargetEnemy(actors[0]);
	actors[1]->SetFiniteStateMachine(blackboard);
	actors[1]->setMaxVelocity(120);*/

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
	Vector2D rand_cell(-1,-1), rand_cell2(-1,-1);
	while (!maze->isValidCell(rand_cell))
		rand_cell = Vector2D((float)(rand() % maze->getNumCellX()), (float)(rand() % maze->getNumCellY()));

	GOAP_Agent->setPosition(maze->cell2pix(rand_cell));
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

	/*for (int i = 0; i < (int)agents.size(); i++)
	{
		delete agents[i];
	}*/

	delete GOAP_Agent;
}

void ScenePathFindingMouse::update(float dtime, SDL_Event *event)
{
	//Update deltaTime global var
	//deltaTime = dtime;
	std::cout << deltaTime << "\n";

	maze->resetTerrainModifiers();

	Vector2D target, start;
	/* Keyboard & Mouse events */
	switch (event->type) {
	case SDL_KEYDOWN:
		if (event->key.keysym.scancode == SDL_SCANCODE_SPACE)
			draw_grid = !draw_grid;

		if (event->key.keysym.scancode == SDL_SCANCODE_RETURN) {
			// Do 20 paths
			start = maze->pix2cell(GOAP_Agent->getPosition());

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
			//agents[0]->SetWalkPoint(Vector2D((float)(event->button.x), (float)(event->button.y)));
		}
		break;
	
	default:
		break;
	}
	blackboard->UpdateConditionsState(GOAP_Agent, FSM_Agent, maze);

	// Update Algorithms
	//GOAP_Algorithm->Update();
	GOAP_Agent->UpdateEnemy();
	FSM_Agent->UpdateEnemy();

	//Update enemies
	//UpdateEnemies(dtime, event);
	if (GOAP_Agent->getPathSize() > 0)
		GOAP_Agent->changeVelocityByNodeType(maze->GetNode(maze->pix2cell(GOAP_Agent->getTarget())).GetType());
	if (FSM_Agent->getPathSize() > 0)
		FSM_Agent->changeVelocityByNodeType(maze->GetNode(maze->pix2cell(FSM_Agent->getTarget())).GetType());
	//Update player
	GOAP_Agent->update(dtime, event);
	FSM_Agent->update(dtime, event);

	// PLAYER 1
	/*int sizeMax = 0;
	//if (agents[0]->getPathSize() > 0) { sizeMax = agents[0]->getPathSize() - 1; }
	int currentTargetIndex = GOAP_Agent->getCurrentTargetIndex();
	if (currentTargetIndex < 0) { currentTargetIndex = 0; }
	int futTarget =  clamp(currentTargetIndex + ((GOAP_Agent->getPathSize() - currentTargetIndex) / 2), GOAP_Agent->getPathSize(), currentTargetIndex);
	if (futTarget > GOAP_Agent->getPathSize())
	{
		actor->UpdateEnemy();
		actor->update(dtime, event);
		actor->updatePath();
	}
	for (int i = currentTargetIndex; i < futTarget; i++)
	{
		if(i >= GOAP_Agent->getPathSize())
		{
			i = futTarget;
			int e = GOAP_Agent->getPathSize();
		}
		if (maze->terrain_modifiers.find(maze->GetNode(maze->pix2cell(GOAP_Agent->getPathPoint(i)))) != maze->terrain_modifiers.end())
		{
			GOAP_Agent->clearPath();
			std::stack<Node> path;
			int n;
			path = PathFinding::AStar(maze, maze->pix2cell(GOAP_Agent->getPosition()), targetCell, n);

			while (!path.empty()) {
				GOAP_Agent->addPathPoint(maze->cell2pix(path.top().GetPos()));
				path.pop();
			}
			i = futTarget;
		}
	}*/

	// PLAYER 2
	/*int currentTargetIndex2 = FSM_Agent->getCurrentTargetIndex();
	if (currentTargetIndex2 < 0) { currentTargetIndex2 = 0; }
	int futTarget2 = clamp(currentTargetIndex2 + ((FSM_Agent->getPathSize() - currentTargetIndex2) / 2), FSM_Agent->getPathSize(), currentTargetIndex2);
	if (futTarget2 > FSM_Agent->getPathSize())
	{
		futTarget2 = FSM_Agent->getPathSize();
	}
	for (int i = currentTargetIndex2; i < futTarget2; i++)
	{
		if (i >= FSM_Agent->getPathSize())
		{
			i = futTarget2;
			int e = FSM_Agent->getPathSize();
		}
		if (maze->terrain_modifiers.find(maze->GetNode(maze->pix2cell(FSM_Agent->getPathPoint(i)))) != maze->terrain_modifiers.end())
		{
			FSM_Agent->clearPath();
			std::stack<Node> path;
			int n;
			path = PathFinding::AStar(maze, maze->pix2cell(FSM_Agent->getPosition()), targetCell, n);

			while (!path.empty()) {
				FSM_Agent->addPathPoint(maze->cell2pix(path.top().GetPos()));
				path.pop();
			}
			i = futTarget2;
		}
	}*/
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



	GOAP_Agent->draw(color, color, 0, color);
	FSM_Agent->draw(color, color, 0, color);
    
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
