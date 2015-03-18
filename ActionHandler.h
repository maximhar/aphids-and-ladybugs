#pragma once
#include "Creature.h"
#include "CreatureIterator.h"
class ActionHandler
{
public:
	virtual void moved(Creature& self, Cell& location, int direction) = 0;
	virtual void killed(Creature& self, Cell& location, Creature& victim) = 0;
	virtual void reproduced(Creature& self, Cell& location, Creature& partner, Creature& offspring) = 0;
	virtual CreatureIterator & getContentsIterator(Cell& location) = 0;
	virtual void destroyContentsIterator(CreatureIterator& iterator) = 0;
	virtual CreatureCounter getCounter(Cell& location) = 0;
	virtual bool canChange(Creature & creature) = 0;
};