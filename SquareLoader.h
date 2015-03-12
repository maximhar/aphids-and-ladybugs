#pragma once
#include "Loader.h"
#include "SquareWorld.h"

class SquareLoader : public Loader
{
private:
	void place(std::map<Cell *, std::vector<Creature *>> * map, SquareWorld * world, Creature * creature, int col, int row);
public:
	virtual bool load(std::map<Cell *, std::vector<Creature *>> ** map, World ** world, std::istream & is);
};

