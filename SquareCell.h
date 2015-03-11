#pragma once

#include "Cell.h"
#include <exception>
#include <cstring>

class SquareCell : public Cell 
{

private:

	Cell * neighbours[4];
	const int first = 0, last = 3;

protected:

	virtual void setNeighbour(int index, Cell * cell)
	{
		if (index >= first && index <= last)
		{
			neighbours[index] = cell;
		}
		else throw 1;
	}

public:

	SquareCell()
	{
		memset(neighbours, (int)Cell::EDGE, sizeof(Cell *) * (last + 1));
	}

	virtual int firstNeighbour()
	{
		return first;
	}

	virtual int lastNeighbour() {
		return last;
	}

	virtual Cell * getNeighbour(int index)
	{
		if (index >= first && index <= last)
		{
			return neighbours[index];
		}
		else return NULL;
	}

	static const int LEFT = 0;
	static const int TOP = 1;
	static const int RIGHT = 2;
	static const int BOTTOM = 3;
};