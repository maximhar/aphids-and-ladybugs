#pragma once

#include <exception>

class Cell
{
	friend class World;
protected:
	virtual void setNeighbour(int index, Cell * cell) = 0;
public:
	virtual Cell * getNeighbour(int index) = 0;
	virtual int firstNeighbour() = 0;
	virtual int lastNeighbour() = 0;
};