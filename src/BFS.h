#pragma once
#include "Grid.h"
#include <queue>
#include <stack>

class BFS {
private:
	static bool NodeVisited(Node currentNode, const std::vector<std::vector<bool>> &visitedNodes) {

		return visitedNodes[currentNode.GetPos().y][currentNode.GetPos().x];
	}


public:
	static std::stack<Node> GetPath(Grid *maze, Vector2D start, Vector2D target) {
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

};