#pragma once

#include <iterator>
#include <map>
#include <ostream>
#include "Creature.h"
#include "World.h"

class Printer
{
public:
	virtual void print(std::multimap<Cell *, Creature *> & map, std::ostream & os) = 0;
};