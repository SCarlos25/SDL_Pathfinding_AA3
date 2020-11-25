#include "PathFinding.h"

bool PathFinding::NodeVisited(Node currentNode, const std::vector<std::vector<bool>> &visitedNodes) {

	return visitedNodes[currentNode.GetPos().y][currentNode.GetPos().x];
}

float PathFinding::CalculateCostSoFar(const PathData &cameFrom, Node &currentNode, Node &neighborNode)
{
	return cameFrom.costSoFar + (Vector2D::Distance(currentNode.GetPos(), neighborNode.GetPos()) /** currentNode.GetCost()*/ * neighborNode.GetCost());
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

	std::queue<Node> frontier;
	frontier.push(maze->GetNode(start));
	float bestCostSoFar = -1;
	//bool targetReached = false;

	std::vector<std::vector<bool>> visited(maze->getNumCellY());
	std::vector<std::vector<PathData>> cameFrom(maze->getNumCellY());
	for (int i = 0; i < maze->getNumCellY(); i++)
	{
		std::vector<bool> tempBoolVector(maze->getNumCellX(), false);
		visited[i] = tempBoolVector;
		std::vector<PathData> tempVec2Vector(maze->getNumCellX());
		cameFrom[i] = tempVec2Vector;
	}
	visited[start.y][start.x] = true;

	while (!frontier.empty()) {
		Node currentNode = frontier.front();
		//if (currentNode.GetPos() == target) {
		//	float currentNodeCostSoFar = cameFrom[target.y][target.x].costSoFar;
		//	if (bestCostSoFar <= 0 || currentNodeCostSoFar < bestCostSoFar) {
		//		bestCostSoFar = currentNodeCostSoFar;
		//		//cameFrom[target.y][target.x].cameFrom
		//	}

		//	//Crec que ja no s'hauria de fer el break => S'hauria de fer que no fes push al frontier si el currentNodeSoFar es major al bestCostSoFar quan bestCostSoFar <= 0
		//	//break;
		//}
		frontier.pop();

		//PathData aux;
		std::queue<Node> neighbors = maze->getNeighbors(currentNode.GetPos());
		while (!neighbors.empty()) {
			if (!NodeVisited(neighbors.front(), visited)) {
				visited[neighbors.front().GetPos().y][neighbors.front().GetPos().x] = true;	//Todo: averiguar com treure els visited
				float currentCostSoFar = CalculateCostSoFar(cameFrom[currentNode.GetPos().y][currentNode.GetPos().x], currentNode, neighbors.front());
				//PathData cameFromData = PathData(currentNode.GetPos().y, CalculateCostSoFar(cameFromData, currentNode, neighbors.front()), NULL);
				if (currentCostSoFar < bestCostSoFar || bestCostSoFar <= 0) {
					frontier.push(neighbors.front());

					if (neighbors.front().GetPos() == target) {
						bestCostSoFar = currentCostSoFar;
					}

					cameFrom[neighbors.front().GetPos().y][neighbors.front().GetPos().x] = PathData(
						currentNode.GetPos(),
						currentCostSoFar,
						NULL);
					//aux = cameFrom[neighbors.front().GetPos().y][neighbors.front().GetPos().x];

					//neighbors.front().SetOriginNode(currentNode.GetPos());
					//maze->GetNode(neighbors.front().GetPos()).SetOriginNode(currentNode);
				}
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
		lastNode = maze->GetNode(cameFrom[lastNode.GetPos().y][lastNode.GetPos().x].cameFrom);
		//lastNode = lastNode.GetOriginNode();
	} while (lastNode.GetPos() != start);


	return path;
}