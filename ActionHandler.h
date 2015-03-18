#pragma once
#include "Creature.h"

class ActionHandler
{
public:
	virtual void moved(Creature& self, Cell& location, int direction) = 0;
	virtual void killed(Creature& self, Cell& location, Creature& victim) = 0;
	virtual void reproduced(Creature& self, Cell& location, Creature& partner, Creature& offspring) = 0;
	virtual bool canChange(Creature & creature) = 0;
};