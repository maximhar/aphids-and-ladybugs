#pragma once

#include <iterator>
#include <map>
#include <ostream>
#include "Creature.h"
#include "WorldMap.h"
class Printer
{
public:
	virtual void print(WorldMap & map, std::ostream & os) = 0;
};