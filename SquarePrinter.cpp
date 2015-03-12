#include "SquarePrinter.h"
#include "SquareCell.h"
#include "SquareWorld.h"
#include "CreatureCounter.h"
#include <ostream>
#include <utility>
#include <map>


SquarePrinter::SquarePrinter(SquareWorld * world) : world(world) { }
void SquarePrinter::print(std::map<Cell *, std::vector<Creature *>> & map, std::ostream & os)
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
			auto rit = map.find(cc);
			counter.reset();
			if (rit != map.end()) 
			{
				auto range = rit->second;
				for (auto iter = range.begin(); iter != range.end(); iter++){
					(*iter)->count(counter);
				}
			}
			os << counter.getAphids() << counter.getLadybugs();
			cc = cc->getNeighbour(SquareCell::RIGHT);
		}
		os << std::endl;
		cr = cr->getNeighbour(SquareCell::BOTTOM);
		cc = cr;
	}
}