#pragma once
#include "Creature.h"
#include "CreatureCounter.h"
#include "CreatureInteractor.h"
#define APHID_LIFE 60
class Aphid : public Creature, public CreatureInteractor
{
protected:
	void move();
	void kill();
	void procreate();
	void suicide();
public:
	void interactWith(CreatureInteractor & creature);
	void interact(Aphid & creature);
	void interact(Ladybug & creature);
	Aphid(int lifespan) : Creature(lifespan) { }
};

