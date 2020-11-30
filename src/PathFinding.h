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

		PathData() : cameFrom(-1, -1), costSoFar(-1), heuristic(-1){}
		PathData(Vector2D _cameFrom, float _costSoFar, float _heuristic) : cameFrom(_cameFrom), costSoFar(_costSoFar), heuristic(_heuristic){}
		PathData(PathData &pd) : cameFrom(pd.cameFrom), costSoFar(pd.costSoFar), heuristic(pd.heuristic){}

	};

	static bool NodeVisited(Node currentNode, const std::vector<std::vector<bool>> &visitedNodes);
	static bool NodeVisited(Node currentNode, const std::vector<std::vector<PathData>> &visitedNodes);
	static bool NodeValid(Node currentNode, const std::vector<std::vector<PathData>>& visitedNodes, const float &currentCostSoFar);
	static float CalculateCostSoFar(const float &costSoFar, Node &currentNode, Node &neighborNode);
	static float GetDist(Node &actualNode, Node &neighborNode);
	static float Heuristic(Vector2D start, Vector2D end);

public:
	static std::stack<Node> BFS(Grid *maze, Vector2D start, Vector2D target);
	static std::stack<Node> Dijkstra(Grid *maze, Vector2D start, Vector2D target);
	static std::stack<Node> AStar(Grid *maze, Vector2D start, Vector2D target);
	static std::stack<Node> PathFinding::Greedy(Grid *maze, Vector2D start, Vector2D target);

};