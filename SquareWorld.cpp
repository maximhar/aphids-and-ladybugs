#include "SquareWorld.h"
#include "SquareCell.h"
#include "SquarePrinter.h"
#include <ostream>


int SquareWorld::to2D(int x, int y) {
	return x * height + y;
}

void SquareWorld::initialiseGrid(int width, int height)
{
	for (int col = 0; col < width; col++)
	{
		for (int row = 0; row < height; row++)
		{
			SquareCell * tmp = new SquareCell();
			if (row != 0)
			{
				setCellNeighbour(tmp, &cellAt(to2D(col, row - 1)), SquareCell::TOP);
				setCellNeighbour(&cellAt(to2D(col, row - 1)), tmp, SquareCell::BOTTOM);
			}
			if (col != 0)
			{
				setCellNeighbour(tmp, &cellAt(to2D(col - 1, row)), SquareCell::LEFT);
				setCellNeighbour(&cellAt(to2D(col - 1, row)), tmp, SquareCell::RIGHT);

				if (row > 0)
				{
					setCellNeighbour(tmp, &cellAt(to2D(col - 1, row - 1)), SquareCell::TOP_LEFT);
					setCellNeighbour(&cellAt(to2D(col - 1, row - 1)), tmp, SquareCell::BOTTOM_RIGHT);
				}
				
				if (row < (height - 1))
				{
					setCellNeighbour(tmp, &cellAt(to2D(col - 1, row + 1)), SquareCell::BOTTOM_LEFT);
					setCellNeighbour(&cellAt(to2D(col - 1, row + 1)), tmp, SquareCell::TOP_RIGHT);
				}
			}
			cellSet(to2D(col, row), tmp);
		}
	}
}

SquareWorld::SquareWorld(int width, int height) : World(width * height, new SquarePrinter(this)), width(width), height(height)
{
	initialiseGrid(width, height);
}

Cell & SquareWorld::getOrigin()
{
	return cellAt(0);
}

int SquareWorld::getWidth() { return width; }
int SquareWorld::getHeight() { return height; }