#pragma once

#include <ostream>
#include "World.h"
#include "Cell.h"

class SquareWorld : public World
{
private:
	int width, height;

	int to2D(int x, int y);
	void initialiseGrid(int width, int height);
public:
	SquareWorld(int width, int height);
	virtual Cell & getOrigin();
	int getWidth();
	int getHeight();
};