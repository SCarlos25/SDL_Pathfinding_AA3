#pragma once
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <time.h>
#include "Agent.h"

struct Node {
	int type;	//Tipo de casilla
	float weight;	//Para la heuristica
	float cost;	//Para la distance

	Node(int _type) {
		type = _type;
		switch (type)
		{
		case 0:
			weight = 9001;
			cost = 9001;
			break;

		case 1:
			weight = 1;
			cost = 1;
			break;

		case 2:
			weight = 0.5f;
			cost = 0.5f;
			break;

		case 3:
			weight = 3;
			cost = 3;
			break;

		default:
			break;
		}

	}

};

class Grid
{
public:
	Grid(char* filename);
	~Grid();

private:
	int num_cell_x;
	int num_cell_y;

	std::vector< std::vector<Node> > terrain;

public:
	Vector2D cell2pix(Vector2D cell);
	Vector2D pix2cell(Vector2D pix);
	bool isValidCell(Vector2D cell);
	int GetType(Vector2D cell);
	int getNumCellX();
	int getNumCellY();
};
