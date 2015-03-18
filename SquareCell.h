#pragma once

#include "Cell.h"
#include <cstring>

class SquareCell : public Cell 
{

private:

	Cell * neighbours[8];
	const int last = 7;

protected:

	virtual void setNeighbour(int index, Cell * cell)
	{
		if (index >= 0 && index <= last)
		{
			neighbours[index] = cell;
		}
		else throw 1;
	}

public:

	SquareCell()
	{
		std::memset(neighbours, (int)Cell::EDGE, sizeof(Cell *) * (last + 1));
	}

	virtual int neighbourCount() { return last + 1; }

	virtual Cell * getNeighbour(int index)
	{
		if (index >= 0 && index <= last)
		{
			return neighbours[index];
		}
		else return NULL;
	}

	static const int LEFT = 0;
	static const int TOP_LEFT = 1;
	static const int TOP = 2;
	static const int TOP_RIGHT = 3;
	static const int RIGHT = 4;
	static const int BOTTOM_RIGHT = 5;
	static const int BOTTOM = 6;
	static const int BOTTOM_LEFT = 7;
};