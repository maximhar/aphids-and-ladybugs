#pragma once

#include "Printer.h"
#include "World.h"
#include <ostream>
#include <utility>
#include <map>

class SquarePrinter : public Printer
{
private:
	World * world;
public:
	SquarePrinter(World * world) : world(world) { }
	virtual void print(std::multimap<Cell *, Creature *> & map, std::ostream & os)
	{
		os << "Square World: " << std::endl;
		Cell * cr = &world->getOrigin();
		Cell * cc = cr;

		while (cr != NULL)
		{
			while (cc != NULL)
			{
				os << " ";
				auto range = map.equal_range(cc);
				int count = 0;
				for (auto iter = range.first; iter != range.second; iter++){
					count++;
				}
				os << count;
				cc = cc->getNeighbour(SquareCell::RIGHT);
			}
			os << std::endl;
			cr = cr->getNeighbour(SquareCell::BOTTOM);
			cc = cr;
		}
	}
};