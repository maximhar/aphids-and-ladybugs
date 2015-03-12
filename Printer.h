#pragma once

#include <iterator>
#include <map>
#include <ostream>
#include "Creature.h"

class Printer
{
public:
	virtual void print(std::map<Cell *, std::vector<Creature *>> & map, std::ostream & os) = 0;
};