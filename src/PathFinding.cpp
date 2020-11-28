#include "PathFinding.h"

bool PathFinding::NodeVisited(Node currentNode, const std::vector<std::vector<bool>> &visitedNodes) {

	return visitedNodes[currentNode.GetPos().y][currentNode.GetPos().x];
}
bool PathFinding::NodeVisited(Node currentNode, const std::vector<std::vector<PathData>> &visitedNodes) {

	return visitedNodes[currentNode.GetPos().y][currentNode.GetPos().x].costSoFar >= 0;
}

bool PathFinding::NodeValid(Node currentNode, const std::vector<std::vector<PathData>>& visitedNodes, const float &currentCostSoFar)
{
	return visitedNodes[currentNode.GetPos().y][currentNode.GetPos().x].costSoFar > currentCostSoFar;
}

float PathFinding::CalculateCostSoFar(const float &costSoFar, Node &currentNode, Node &neighborNode)
{
	return costSoFar + (Vector2D::Distance(currentNode.GetPos(), neighborNode.GetPos()) * neighborNode.GetCost());
}

void PathFinding::DijkstraSort(std::deque<std::pair<Node, float>> &frontier)
{
	//Ordered with Selection Sort
	for (int i = 0; i < frontier.size(); i++)
	{
		int imin = i;
		for (int j = i + 1; j < frontier.size(); j++)
		{
			if (frontier[j].second < frontier[imin].second)
				imin = j;
		}
		std::pair<Node, float> aux = frontier[i];
		frontier[i] = frontier[imin];
		frontier[imin] = aux;
	}
}

std::stack<Node> PathFinding::BFS(Grid * maze, Vector2D start, Vector2D target)
{
	if (start == target) {
		std::stack<Node> path;
		path.push(maze->GetNode(start));
		return path;
	}

	std::queue<Node> frontier;
	frontier.push(maze->GetNode(start));

	std::vector<std::vector<bool>> visited(maze->getNumCellY());
	std::vector<std::vector<Vector2D>> cameFrom(maze->getNumCellY());
	for (int i = 0; i < maze->getNumCellY(); i++)
	{
		std::vector<bool> tempBoolVector(maze->getNumCellX(), false);
		visited[i] = tempBoolVector;
		std::vector<Vector2D> tempVec2Vector(maze->getNumCellX());
		cameFrom[i] = tempVec2Vector;
	}
	visited[start.y][start.x] = true;

	while (!frontier.empty()) {
		Node currentNode = frontier.front();
		if (currentNode.GetPos() == target) {
			break;
		}
		frontier.pop();

		std::queue<Node> neighbors = maze->getNeighbors(currentNode.GetPos());
		while (!neighbors.empty()) {
			if (!NodeVisited(neighbors.front(), visited)) {
				frontier.push(neighbors.front());

				visited[neighbors.front().GetPos().y][neighbors.front().GetPos().x] = true;
				cameFrom[neighbors.front().GetPos().y][neighbors.front().GetPos().x] = currentNode.GetPos();
				//neighbors.front().SetOriginNode(currentNode.GetPos());
				//maze->GetNode(neighbors.front().GetPos()).SetOriginNode(currentNode);
			}
			neighbors.pop();
		}

		//cameFrom.push(currentNode);
	}

	std::stack<Node> path;
	//Node lastNode = cameFrom[target.y][target.x];
	Node lastNode = maze->GetNode(target);
	do {
		path.push(lastNode);
		lastNode = maze->GetNode(cameFrom[lastNode.GetPos().y][lastNode.GetPos().x]);
		//lastNode = lastNode.GetOriginNode();
	} while (lastNode.GetPos() != start);


	return path;
}


std::stack<Node> PathFinding::Dijkstra(Grid *maze, Vector2D start, Vector2D target) {
	if (start == target) {
		std::stack<Node> path;
		path.push(maze->GetNode(start));
		return path;
	}

	//std::priority_queue<std::pair<Node, float>, dijkstraComparison> frontier;
	std::deque<std::pair<Node, float>> frontier;
	frontier.push_back(std::make_pair(maze->GetNode(start), 0));
	float bestCostSoFar = -1;
	//bool targetReached = false;

	//std::vector<std::vector<bool>> visited(maze->getNumCellY());
	std::vector<std::vector<PathData>> cameFrom(maze->getNumCellY());
	for (int i = 0; i < maze->getNumCellY(); i++)
	{
		//std::vector<bool> tempBoolVector(maze->getNumCellX(), false);
		//visited[i] = tempBoolVector;
		std::vector<PathData> tempVec2Vector(maze->getNumCellX());
		cameFrom[i] = tempVec2Vector;
	}
	//visited[start.y][start.x] = true;
	cameFrom[start.y][start.x].costSoFar = 0;

	while (!frontier.empty()) {
		//std::pair<Node, float> currentNode = frontier.top();	//top() == front() del queue
		//if (currentNode.GetPos() == target) {
		//	float currentNodeCostSoFar = cameFrom[target.y][target.x].costSoFar;
		//	if (bestCostSoFar <= 0 || currentNodeCostSoFar < bestCostSoFar) {
		//		bestCostSoFar = currentNodeCostSoFar;
		//		//cameFrom[target.y][target.x].cameFrom
		//	}

		//	//Crec que ja no s'hauria de fer el break => S'hauria de fer que no fes push al frontier si el currentNodeSoFar es major al bestCostSoFar quan bestCostSoFar <= 0
		//	//break;
		//}
		std::pair<Node, float> currentNode = frontier.front();
		frontier.pop_front();

		//PathData aux;
		std::queue<Node> neighbors = maze->getNeighbors(currentNode.first.GetPos());
		while (!neighbors.empty()) {
			float currentCostSoFar = CalculateCostSoFar(currentNode.second, currentNode.first, neighbors.front());
			if ((!NodeVisited(neighbors.front(), cameFrom) || NodeValid(neighbors.front(), cameFrom, currentCostSoFar))
				&& !(bestCostSoFar >= 0 && currentCostSoFar > currentCostSoFar)) 
			{
				cameFrom[neighbors.front().GetPos().y][neighbors.front().GetPos().x] = PathData(
					currentNode.first.GetPos(),
					currentCostSoFar,
					NULL);
				PathData aux = cameFrom[neighbors.front().GetPos().y][neighbors.front().GetPos().x];

				frontier.push_back(std::make_pair(neighbors.front(), currentCostSoFar));


				if (neighbors.front().GetPos() == target) {
					bestCostSoFar = currentCostSoFar;
					//break;
				}

				////visited[neighbors.front().GetPos().y][neighbors.front().GetPos().x] = true;	//Todo: averiguar com treure els visited
				////PathData cameFromData = PathData(currentNode.GetPos().y, CalculateCostSoFar(cameFromData, currentNode, neighbors.front()), NULL);
				//if (currentCostSoFar < bestCostSoFar || bestCostSoFar <= 0) {
				//	frontier.push(neighbors.front());

				//	if (neighbors.front().GetPos() == target) {
				//		bestCostSoFar = currentCostSoFar;
				//	}

				//	cameFrom[neighbors.front().GetPos().y][neighbors.front().GetPos().x] = PathData(
				//		currentNode.GetPos(),
				//		currentCostSoFar,
				//		NULL);
				//	//aux = cameFrom[neighbors.front().GetPos().y][neighbors.front().GetPos().x];

				//	//neighbors.front().SetOriginNode(currentNode.GetPos());
				//	//maze->GetNode(neighbors.front().GetPos()).SetOriginNode(currentNode);
				//}
			}
			neighbors.pop();
		}

		DijkstraSort(frontier);

		//cameFrom.push(currentNode);
	}

	std::stack<Node> path;
	//Node lastNode = cameFrom[target.y][target.x];
	Node lastNode = maze->GetNode(target);
	do {
		path.push(lastNode);
		lastNode = maze->GetNode(cameFrom[lastNode.GetPos().y][lastNode.GetPos().x].cameFrom);
		//lastNode = lastNode.GetOriginNode();
	} while (lastNode.GetPos() != start);


	return path;
}