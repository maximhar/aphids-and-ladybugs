#pragma once
#include <map>
#include <vector>
#include "Cell.h"
#include "Creature.h"
#include "World.h"
#include "WorldMap.h"
class Loader
{
public:
	virtual World * load(WorldMap * map, std::istream & is) = 0;
};