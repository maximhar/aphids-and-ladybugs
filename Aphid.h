#pragma once
#include "Creature.h"
#include "CreatureCounter.h"
class Aphid : public Creature
{
public:
	void count(CreatureCounter & counter) { counter.count(*this); }
	void update(ActionHandler & handler, Cell & location, std::pair<std::vector<Creature *>::iterator, std::vector<Creature * >::iterator> contents);
	void interactWith(Creature & creature);
	void interact(Aphid & creature);
	void interact(Ladybug & creature);
};

