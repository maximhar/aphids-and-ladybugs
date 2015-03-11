#pragma once
#include <map>
#include "Cell.h"
#include "Creature.h"
#include "World.h"

class Loader
{
public:
	virtual bool load(std::multimap<Cell *, Creature *> ** map, World ** world, std::istream & is) = 0;
};