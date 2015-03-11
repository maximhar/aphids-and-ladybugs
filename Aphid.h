#pragma once
#include "Creature.h"
#include "CreatureCounter.h"
class Aphid : public Creature
{
public:
	void count(CreatureCounter & counter) { counter.count(*this); }
};

