#pragma once
#include "Grid.h"
#include <queue>
#include <stack>
#include <unordered_map>

class Priority_Node
{
public:
	Node node;
	float priority;

	Priority_Node(Node gNode, float gPriority);

public:
	//Overload the < operator
	bool friend operator< (const Priority_Node& node1, const Priority_Node &node2);
	//Overload the > operator
	bool friend operator> (const Priority_Node& node1, const Priority_Node &node2);
};

class PathFinding {
private:
	struct PathData {
		Vector2D cameFrom;
		float costSoFar;
		float heuristic;

		PathData() : cameFrom(NULL, NULL), costSoFar(NULL), heuristic(NULL){}
		PathData(Vector2D _cameFrom, float _costSoFar, float _heuristic) : cameFrom(_cameFrom), costSoFar(_costSoFar), heuristic(_heuristic){}
		PathData(PathData &pd) : cameFrom(pd.cameFrom), costSoFar(pd.costSoFar), heuristic(pd.heuristic){}

	};

	static bool NodeVisited(Node currentNode, const std::vector<std::vector<bool>> &visitedNodes);
	static float CalculateCostSoFar(const PathData &cameFrom, Node &currentNode, Node &neighborNode);
	static float Heuristic(Vector2D start, Vector2D end);

public:
	static std::stack<Node> BFS(Grid *maze, Vector2D start, Vector2D target);
	static std::stack<Node> Dijkstra(Grid *maze, Vector2D start, Vector2D target);
	static std::stack<Node> AStar(Grid *maze, Vector2D start, Vector2D target);

};