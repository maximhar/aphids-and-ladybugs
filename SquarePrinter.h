#pragma once

#include "Printer.h"
#include <ostream>
#include <utility>
#include <map>

class SquareWorld;

class SquarePrinter : public Printer
{
private:
	SquareWorld * world;
public:
	SquarePrinter(SquareWorld * world);
	virtual void print(std::multimap<Cell *, Creature *> & map, std::ostream & os);
};