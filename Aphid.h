#pragma once
#include "Creature.h"
#include "CreatureCounter.h"
#include "CreatureInteractor.h"
#define APHID_LIFE 50
#define APHID_NUT_VAL 100.0f
#define APHID_START_FOOD 10000.0f
class Aphid : public Creature, public CreatureInteractor
{
protected:
	void move();
	void kill();
	void procreate();
	void suicide();
	float eat();
public:
	void interactWith(CreatureInteractor & creature);
	void interact(Aphid & creature);
	void interact(Ladybug & creature);
	Aphid(int lifespan, float startFood) : Creature(lifespan, APHID_NUT_VAL, startFood) { }
};

