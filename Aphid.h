#pragma once
#include "Creature.h"
#include "CreatureCounter.h"
#include "CreatureInteractor.h"
class Aphid : public Creature, public CreatureInteractor
{
public:
	void update(ActionHandler & handler, Cell & location, std::pair<std::vector<Creature *>::iterator, std::vector<Creature * >::iterator> contents);
	void interactWith(CreatureInteractor & creature);
	void interact(Aphid & creature);
	void interact(Ladybug & creature);
};

