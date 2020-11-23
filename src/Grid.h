#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <queue>
#include "Agent.h"
#include "Node.h"


class Grid
{
public:
	Grid(char* filename);
	~Grid();

private:
	int num_cell_x;
	int num_cell_y;

	std::vector< std::vector<Node> > terrain;

	bool OverlapsWall(int i, int j, Vector2D checkPos);

public:
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	std::queue<Node> getNeighbors(Vector2D vectorPosition);
	bool isValidCell(Vector2D cell);
	int GetType(Vector2D cell);
	Node GetNode(Vector2D cell);
	int getNumCellX();
	int getNumCellY();


};
