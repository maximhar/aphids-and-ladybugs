#pragma once

#include <vector>
#include "Creature.h"

class Cell
{
	friend class World;
protected:
	virtual void setNeighbour(int index, Cell * cell) = 0;
public:
	virtual Cell * getNeighbour(int index) = 0;
	virtual int neighbourCount() = 0;
	static const Cell * EDGE;
};