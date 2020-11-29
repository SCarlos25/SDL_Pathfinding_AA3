#include "Grid.h"

using namespace std;

Grid::Grid(char* filename)
{
	num_cell_x = SRC_WIDTH / CELL_SIZE;
	num_cell_y = SRC_HEIGHT / CELL_SIZE;

	// Initialize the terrain matrix from file (for each cell a zero value indicates it's a wall, positive values indicate terrain cell cost)
	std::ifstream infile(filename);
	std::string line;
	int i = 0;
	while (std::getline(infile, line))
	{
		vector<Node> terrain_row;
		std::stringstream lineStream(line);
		std::string cell;
		int j = 0;
		while (std::getline(lineStream, cell, ','))
		{
			terrain_row.push_back(Node(atoi(cell.c_str()), Vector2D(j, i)));
			j++;
		}
		SDL_assert(terrain_row.size() == num_cell_x);
		terrain.push_back(terrain_row);
		i++;
	}
	SDL_assert(terrain.size() == num_cell_y);
	infile.close();
}

Grid::~Grid()
{
}

int Grid::getNumCellX()
{
	return num_cell_x;
}

int Grid::getNumCellY()
{
	return num_cell_y;
}

Vector2D Grid::cell2pix(Vector2D cell)
{
	int offset = CELL_SIZE / 2;
	return Vector2D(cell.x*CELL_SIZE + offset, cell.y*CELL_SIZE + offset);
}

Vector2D Grid::pix2cell(Vector2D pix)
{
	int x = (float)((int)pix.x / CELL_SIZE);
	int y = (float)((int)pix.y / CELL_SIZE);

	return Vector2D((float)((int)pix.x / CELL_SIZE), (float)((int)pix.y / CELL_SIZE));
}

bool Grid::isValidCell(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.y >= terrain.size()) || (cell.x >= terrain[0].size()))
		return false;
	return !(terrain[(unsigned int)cell.y][(unsigned int)cell.x].GetType() == 0);
}

int Grid::GetType(Vector2D cell)
{
	if ((cell.x < 0) || (cell.y < 0) || (cell.y >= terrain.size()) || (cell.x >= terrain[0].size()))
		return -1;
	return terrain[(unsigned int)cell.y][(unsigned int)cell.x].GetType();
}

Node Grid::GetNode(Vector2D cell)
{
	return terrain[cell.y][cell.x];
}

//Returns true if the path to the neighbor would overlap a wall
bool Grid::OverlapsWall(bool yTrigger, bool xTrigger, Vector2D nodePos) {
	if (!yTrigger && !xTrigger) {
		return terrain[nodePos.y - 1][nodePos.x].GetType() == 0 || terrain[nodePos.y][nodePos.x - 1].GetType() == 0;
	}
	else if (yTrigger && !xTrigger) {
		return terrain[nodePos.y + 1][nodePos.x].GetType() == 0 || terrain[nodePos.y][nodePos.x - 1].GetType() == 0;
	}
	else if (!yTrigger && xTrigger) {
		return terrain[nodePos.y - 1][nodePos.x].GetType() == 0 || terrain[nodePos.y][nodePos.x + 1].GetType() == 0;
	}
	else if (yTrigger && xTrigger) {
		return terrain[nodePos.y + 1][nodePos.x].GetType() == 0 || terrain[nodePos.y][nodePos.x + 1].GetType() == 0;
	}
	else {
		return false;
	}

}

//Le pasamos una posicion vector que NO sea un pixel de la pantalla y que sean las coordenadas de nodo
std::queue<Node> Grid::getNeighbors(Vector2D nodePos)
{
	std::queue<Node> returnResult;

	if ((nodePos.x > 0) && (nodePos.y > 0) && (nodePos.y < terrain.size() - 1) && (nodePos.x < terrain[0].size() - 1)) {
		//Vertical
		if (terrain[nodePos.y - 1][nodePos.x].GetType() != 0) {
			returnResult.push(terrain[nodePos.y - 1][nodePos.x]);
		}
		if (terrain[nodePos.y + 1][nodePos.x].GetType() != 0) {
			returnResult.push(terrain[nodePos.y + 1][nodePos.x]);
		}

		//Horizontal
		if (terrain[nodePos.y][nodePos.x - 1].GetType() != 0) {
			returnResult.push(terrain[nodePos.y][nodePos.x - 1]);
		}
		if (terrain[nodePos.y][nodePos.x + 1].GetType() != 0) {
			returnResult.push(terrain[nodePos.y][nodePos.x + 1]);
		}

		//Diagonal
		if (terrain[nodePos.y - 1][nodePos.x - 1].GetType() != 0 && !OverlapsWall(false, false, nodePos)) {
			returnResult.push(terrain[nodePos.y - 1][nodePos.x - 1]);
		}
		if (terrain[nodePos.y + 1][nodePos.x - 1].GetType() != 0 && !OverlapsWall(true, false, nodePos)) {
			returnResult.push(terrain[nodePos.y + 1][nodePos.x - 1]);
		}
		if (terrain[nodePos.y - 1][nodePos.x + 1].GetType() != 0 && !OverlapsWall(false, true, nodePos)) {
			returnResult.push(terrain[nodePos.y - 1][nodePos.x + 1]);
		}
		if (terrain[nodePos.y + 1][nodePos.x + 1].GetType() != 0 && !OverlapsWall(true, true, nodePos)) {
			returnResult.push(terrain[nodePos.y + 1][nodePos.x + 1]);
		}

	}


	return returnResult;
}
