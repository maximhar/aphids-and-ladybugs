#include "SquarePrinter.h"
#include "SquareCell.h"
#include "SquareWorld.h"
#include "CreatureCounter.h"
#include <ostream>
#include <utility>
#include <map>
#include <sstream>

SquarePrinter::SquarePrinter(SquareWorld * world) : world(world) { }
void SquarePrinter::print(WorldMap & map, std::ostream & os)
{
	os << "Square World: " << std::endl;
	Cell * cr = &world->getOrigin();
	Cell * cc = cr;
	while (cr != Cell::EDGE)
	{
		while (cc != Cell::EDGE)
		{
			os << " ";
			WorldMap::CreatureIterator * creatures = map.creaturesInCell(*cc);
			CreatureCounter counter = map.getCounterForCell(*cc);
			std::stringstream ss;
			if (counter.getAphids() < 10) ss << counter.getAphids();
			else ss << "~";
			if (counter.getLadybugs() < 10) ss << counter.getLadybugs();
			else ss << "~";
			os << ss.str();
			cc = cc->getNeighbour(SquareCell::RIGHT);
		}
		os << std::endl;
		cr = cr->getNeighbour(SquareCell::BOTTOM);
		cc = cr;
	}
}