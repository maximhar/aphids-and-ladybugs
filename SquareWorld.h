#pragma once

#include "World.h"
#include "SquareCell.h"
#include "SquarePrinter.h"
#include <ostream>

class SquareWorld : public World
{
private:
	int width, height;

	int to2D(int x, int y) {
		return x * height + y;
	}

	void initialiseGrid(int width, int height) 
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
				}
				cellSet(to2D(col, row), tmp);
			}
		}
	}
public:
	SquareWorld(int width, int height) : World(width * height, new SquarePrinter(this)), width(width), height(height)
	{ 
		initialiseGrid(width, height);
	}

	virtual Cell & getOrigin()
	{
		return cellAt(0);
	}
};