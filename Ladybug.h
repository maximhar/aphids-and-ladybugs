#pragma once
#include "Creature.h"
#include "CreatureCounter.h"
#include "CreatureInteractor.h"
#define LADYBUG_LIFE 140
class Ladybug : public Creature, public CreatureInteractor
{
private:
	int generalDirection;
protected:
	void move();
	void kill();
	void procreate();
	void suicide();
public:
	void interactWith(CreatureInteractor & creature);
	void interact(Aphid & creature);
	void interact(Ladybug & creature);
	Ladybug(int lifespan) : Creature(lifespan) { }
};

