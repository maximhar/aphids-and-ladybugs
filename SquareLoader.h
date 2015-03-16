#pragma once
#include "Loader.h"
#include "SquareWorld.h"

class SquareLoader : public Loader
{
private:
	void place(WorldMap * map, SquareWorld * world, Creature * creature, int col, int row);
public:
	virtual World * load(WorldMap * map, std::istream & is);
};

