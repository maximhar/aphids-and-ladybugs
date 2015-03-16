#include "SquarePrinter.h"
#include "SquareCell.h"
#include "SquareWorld.h"
#include "CreatureCounter.h"
#include <ostream>
#include <utility>
#include <map>


SquarePrinter::SquarePrinter(SquareWorld * world) : world(world) { }
void SquarePrinter::print(WorldMap & map, std::ostream & os)
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
			WorldMap::CreatureIterator * creatures = map.creaturesInCell(*cc);
			counter.reset();
			if (creatures != NULL) 
			{
				while (creatures->hasNext())
				{
					WorldMap::CreatureCellPair pair = creatures->next();
					pair.creature->interactWith(counter);
				}
				delete creatures;
			}
			os << counter.getAphids() << counter.getLadybugs();
			cc = cc->getNeighbour(SquareCell::RIGHT);
		}
		os << std::endl;
		cr = cr->getNeighbour(SquareCell::BOTTOM);
		cc = cr;
	}
}