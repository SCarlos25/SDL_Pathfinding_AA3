#pragma once
#include "Grid.h"
#include <queue>

class BFS {
private:
	static bool NodeVisited(Node currentNode, std::vector<std::vector<bool>> visitedNodes) {

		return visitedNodes[currentNode.GetPos().y][currentNode.GetPos().x]; // ESTABA AL REVES
	}


public:
	static std::queue<Node> GetPath(Grid *maze, Vector2D start, Vector2D target) {
		std::queue<Node> frontier;
		frontier.push(maze->GetNode(start));

		std::vector<std::vector<bool>> visited(maze->getNumCellY());
		std::vector<std::vector<Node>> cameFrom(maze->getNumCellY());
		for (int i = 0; i < maze->getNumCellY(); i++)
		{
			std::vector<bool> tempBoolVector(maze->getNumCellX(), false);
			visited[i] = tempBoolVector;
			std::vector<Node> tempVec2Vector(maze->getNumCellX());
			cameFrom[i] = tempVec2Vector;
		}


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
					cameFrom[neighbors.front().GetPos().y][neighbors.front().GetPos().x] = currentNode;
				}
				neighbors.pop();
			}

			//cameFrom.push(currentNode);
		}

		std::queue<Node> path;
		Node lastNode = cameFrom[target.y][target.x];
		while (path.back().GetPos() != start) {
			path.push(lastNode);
			lastNode = cameFrom[lastNode.GetPos().y][lastNode.GetPos().x];
		}


		return path;
	}

};