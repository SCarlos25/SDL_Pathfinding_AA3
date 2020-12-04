#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include <queue>
#include <unordered_map>
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

	bool OverlapsWall(bool yTrigger, bool xTrigger, Vector2D checkPos);


public:
	//A unordered map that ONLY keeps track of terrain value modifiers (float values)
	std::unordered_map<Node, float> terrain_modifiers;

	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	std::queue<Node> getNeighbors(Vector2D vectorPosition);
	bool isValidCell(Vector2D cell);
	int GetType(Vector2D cell);
	Node GetNode(Vector2D cell);
	float GetModifierCost(Vector2D cell);
	int getNumCellX();
	int getNumCellY();
	void resetTerrainModifiers();
	void AddTerrainModifier(Vector2D pos, int distX, int distY, float cost);

};
