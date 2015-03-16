#pragma once

#include "Printer.h"
#include <ostream>
#include <utility>
#include <map>
#include <vector> 

class SquareWorld;

class SquarePrinter : public Printer
{
private:
	SquareWorld * world;
public:
	SquarePrinter(SquareWorld * world);
	virtual void print(WorldMap & map, std::ostream & os);
};