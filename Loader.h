#pragma once
#include <map>
#include <vector>
#include "Cell.h"
#include "Creature.h"
#include "World.h"

class Loader
{
public:
	virtual bool load(std::map<Cell *, std::vector<Creature *>> ** map, World ** world, std::istream & is) = 0;
};