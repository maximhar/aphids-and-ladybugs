#pragma once
#include "Creature.h"
#include "CreatureCounter.h"
#include "CreatureInteractor.h"
class Ladybug : public Creature, public CreatureInteractor
{
private:
	int generalDirection;
public:
	void move(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents);
	void kill(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents);
	void procreate(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents);
	void interactWith(CreatureInteractor & creature);
	void interact(Aphid & creature);
	void interact(Ladybug & creature);
};

