#pragma once
#include "Grid.h"
#include <queue>

class BFS {
private:
	static bool NodeVisited(Node currentNode, std::vector<std::vector<bool>> visitedNodes) {

		return visitedNodes[currentNode.GetPos().y][currentNode.GetPos().x];
	}


public:
	static std::queue<Node> GetPath(Grid *maze, Vector2D start, Vector2D target) {
		std::queue<Node> frontier, cameFrom;
		frontier.push(maze->GetNode(start));

		std::vector<std::vector<bool>> visited(maze->getNumCellY());
		for (int i = 0; i < visited.size(); i++)
		{
			std::vector<bool> tempVector(maze->getNumCellX(), false);
			visited[i] = tempVector;
		}


		while (!frontier.empty()) {
			Node currentNode = frontier.back();
			if (currentNode.GetPos() == target) {
				break;
			}
			frontier.pop();

			std::queue<Node> neighbors = maze->getNeighbors(currentNode.GetPos());
			while (!neighbors.empty()) {
				if (!NodeVisited(neighbors.front(), visited)) {
					frontier.push(neighbors.front());

					visited[neighbors.front().GetPos().y][neighbors.front().GetPos().x] = true;
				}
				neighbors.pop();
			}

			cameFrom.push(currentNode);
		}


		return cameFrom;
	}

};