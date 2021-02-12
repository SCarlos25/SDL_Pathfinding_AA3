#pragma once
#include "../src/Vector2D.h"
#include "../src/Grid.h"

namespace Raycast {
	static bool RaycastCollidesWall(Vector2D v1, Vector2D v2, Grid* maze) {
		Vector2D dir = (v2 - v1).Normalize();
		float dist = Vector2D::Distance(v1, v2);
		int cellSize = 32;
		float currDist = cellSize;

		while (currDist < dist) {
			Vector2D raycastCheck = dir * currDist + v1;
			currDist += cellSize;

			if (!maze->isValidCell(maze->pix2cell(raycastCheck)))
				return true;
		}

		return false;
	}

}