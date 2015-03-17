#pragma once
#include "Creature.h"
#include "CreatureCounter.h"
#include "CreatureInteractor.h"
#define LADYBUG_LIFE 140
#define LADYBUG_NUT_VAL 200.0f
#define LADYBUG_START_FOOD 20000.0f
class Ladybug : public Creature, public CreatureInteractor
{
private:
	int generalDirection;
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
	Ladybug(int lifespan, float startFood) : Creature(lifespan, LADYBUG_NUT_VAL, startFood) { }
};

