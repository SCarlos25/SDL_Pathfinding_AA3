#include "PathFinding.h"

Priority_Node::Priority_Node(Node gNode, float gPriority)
{
	node = gNode;
	priority = gPriority;
}

bool operator< (const Priority_Node& node1, const Priority_Node &node2)
{
	return node1.priority > node2.priority;
}

bool operator> (const Priority_Node& node1, const Priority_Node &node2)
{
	return node1.priority < node2.priority;
}

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

float PathFinding::GetDist(Node &actualNode, Node &neighborNode)
{
	if (actualNode.GetPos().x == neighborNode.GetPos().x || actualNode.GetPos().y == neighborNode.GetPos().y)
	{
		return 1;
	}
	else
	{
		return sqrt(2);
	}
}

float PathFinding::Octile(Vector2D start, Vector2D end) {
	float x = abs(start.x - end.x);
	float y = abs(start.y - end.y);
	// Octile Distance
	return max(x, y) + ((sqrt(2) - 1) * min(x, y));
}

std::stack<Node> PathFinding::BFS(Grid *maze, Vector2D start, Vector2D target)
{
	if (start == target) {
		std::stack<Node> path;
		path.push(maze->GetNode(start));
		return path;
	}

	int counterr = 0;

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
		counterr++;
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
			}
			neighbors.pop();
		}

	}

	std::stack<Node> path;
	BFS_nodes.push_back(counterr);

	Node lastNode = maze->GetNode(target);
	do {
		path.push(lastNode);
		lastNode = maze->GetNode(cameFrom[lastNode.GetPos().y][lastNode.GetPos().x]);
	} while (lastNode.GetPos() != start);


	return path;
}

std::stack<Node> PathFinding::Dijkstra(Grid *maze, Vector2D start, Vector2D target) {
	if (start == target) {
		std::stack<Node> path;
		path.push(maze->GetNode(start));
		return path;
	}

	int counterr = 0;

	std::priority_queue<Priority_Node> frontier;
	frontier.push(Priority_Node(maze->GetNode(start), 0));
	float bestCostSoFar = -1;


	std::vector<std::vector<PathData>> cameFrom(maze->getNumCellY());
	for (int i = 0; i < maze->getNumCellY(); i++)
	{
		std::vector<PathData> tempVec2Vector(maze->getNumCellX());
		cameFrom[i] = tempVec2Vector;
	}
	cameFrom[start.y][start.x].costSoFar = 0;

	while (!frontier.empty()) {
		counterr++;
		Priority_Node currentNode = frontier.top();
		frontier.pop();


		std::queue<Node> neighbors = maze->getNeighbors(currentNode.node.GetPos());
		while (!neighbors.empty()) {
			float currentCostSoFar = CalculateCostSoFar(currentNode.priority, currentNode.node, neighbors.front());
			if ((!NodeVisited(neighbors.front(), cameFrom) || NodeValid(neighbors.front(), cameFrom, currentCostSoFar))
				&& !(bestCostSoFar >= 0 && currentCostSoFar > currentCostSoFar)) 
			{
				cameFrom[neighbors.front().GetPos().y][neighbors.front().GetPos().x] = PathData(
					currentNode.node.GetPos(),
					currentCostSoFar,
					NULL);
				PathData aux = cameFrom[neighbors.front().GetPos().y][neighbors.front().GetPos().x];

				frontier.push(Priority_Node(neighbors.front(), currentCostSoFar));


				if (neighbors.front().GetPos() == target) {
					bestCostSoFar = currentCostSoFar;
					//break;
				}

			}
			neighbors.pop();
		}

	}
	std::stack<Node> path;
	Dijkstra_nodes.push_back(counterr);

	if (cameFrom[target.y][target.x].costSoFar >= 0) {
		Node lastNode = maze->GetNode(target);
		do {
			path.push(lastNode);
			lastNode = maze->GetNode(cameFrom[lastNode.GetPos().y][lastNode.GetPos().x].cameFrom);
		} while (lastNode.GetPos() != start);
	}
	else {
		// No ha trobat un caminar fins a target
	}

	return path;
}

std::stack<Node> PathFinding::Greedy(Grid *maze, Vector2D start, Vector2D target) {
	if (start == target) {
		std::stack<Node> path;
		path.push(maze->GetNode(start));
		return path;
	}

	int counterr = 0;

	std::queue<Node> frontier;
	frontier.push(maze->GetNode(start));

	std::unordered_map<Node, Node> came_from;
	came_from[maze->GetNode(start)] = Node();

	Node curr, prev;
	bool exit = false;
	float max_cost = 40;

	while (!frontier.empty())
	{
		counterr++;

		prev = curr;
		curr = frontier.back();
		frontier.pop();

		if (curr.pos == target)
		{
			/* Early Exit */
			came_from[curr] = prev;
			break;
		}

		float actual_cost = Octile(curr.GetPos(), target);
		float best_cost = max_cost;
		Node best_neighbor, now_neighbor;
		std::queue<Node> neighbors = maze->getNeighbors(curr.pos);

		while (!neighbors.empty())
		{
			now_neighbor = neighbors.front();
			neighbors.pop();

			float actual_cost = Octile(now_neighbor.pos, target);

			if (came_from.find(now_neighbor) == came_from.end() && actual_cost < best_cost /*&& !exit*/)
			{
				came_from[now_neighbor] = curr;

				best_cost = actual_cost;
				best_neighbor = now_neighbor;
			}
		}

		if(best_cost != max_cost) frontier.push(best_neighbor);
	}
	std::stack<Node> path;
	Greedy_nodes.push_back(counterr);

	if (curr.pos == target)
	{
		// Rehacer camino atras
		Node tmp = curr;
		path.push(tmp);
		while (came_from[tmp].pos != start)
		{
			path.push(came_from[tmp]);
			tmp = came_from[tmp];
		}
	}


	return path;
}

std::stack<Node> PathFinding::AStar(Grid *maze, Vector2D start, Vector2D target) {
	if (start == target) {
		std::stack<Node> path;
		path.push(maze->GetNode(start));
		return path;
	}

	int counterr = 0;

	std::priority_queue<Priority_Node> frontier;
	frontier.push(Priority_Node(maze->GetNode(start), 0));

	std::unordered_map<Node, Node> came_from;
	came_from[maze->GetNode(start)] = Node();

	std::unordered_map<Node, float> cost_so_far;
	cost_so_far[maze->GetNode(start)] = 0;

	Node current;

	while (!frontier.empty())
	{
		counterr++;

		current = frontier.top().node;
		frontier.pop();
		if(current.pos == target) { break; }

		std::queue<Node> neighbors = maze->getNeighbors(current.pos);
		while (!neighbors.empty())
		{
			Node next = neighbors.front();
			neighbors.pop();

			float new_cost = cost_so_far[current] + Vector2D::Distance(current.pos, next.pos) * next.GetCost();

			if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next])
			{
				cost_so_far[next] = new_cost;
				float priority = new_cost + Octile(target, next.pos);
				frontier.push(Priority_Node(next,priority));
				came_from[next] = current;
			}
		}
	}
	std::stack<Node> path;
	AStar_nodes.push_back(counterr);

	if (frontier.empty() && current.pos != target)
	{
		//No path found!
	}
	else if(current.pos == target)
	{
		//Target found, reconstruct path that we took!
		Node temp = current;
		path.push(temp);
		while (came_from[temp].pos.x != 0 && came_from[temp].pos.y != 0)
		{
			path.push(came_from[temp]);
			temp = came_from[temp];
		}
	}

	return path;
}