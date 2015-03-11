#include "SquarePrinter.h"
#include "SquareCell.h"
#include "SquareWorld.h"
#include "CreatureCounter.h"
#include <ostream>
#include <utility>
#include <map>


SquarePrinter::SquarePrinter(SquareWorld * world) : world(world) { }
void SquarePrinter::print(std::multimap<Cell *, Creature *> & map, std::ostream & os)
{
	os << "Square World: " << std::endl;
	Cell * cr = &world->getOrigin();
	Cell * cc = cr;
	CreatureCounter counter;
	while (cr != Cell::EDGE)
	{
		while (cc != Cell::EDGE)
		{
			os << " ";
			auto range = map.equal_range(cc);
			counter.reset();
			for (auto iter = range.first; iter != range.second; iter++){
				iter->second->count(counter);
			}
			os << counter.getAphids() << ":" << counter.getLadybugs();
			cc = cc->getNeighbour(SquareCell::RIGHT);
		}
		os << std::endl;
		cr = cr->getNeighbour(SquareCell::BOTTOM);
		cc = cr;
	}
}