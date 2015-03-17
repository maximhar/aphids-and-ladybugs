#pragma once
#include "Creature.h"
#include "CreatureCounter.h"
#include "CreatureInteractor.h"
class Ladybug : public Creature, public CreatureInteractor
{
private:
	int generalDirection;
protected:
	void move();
	void suicide();
	float eat();
	float getDefaultNutritionalValue();
	void interactImpl(Creature * creature) { creature->interactWith(*this); }
	int getDirection();
	float getMoveProbability();
public:
	void interactWith(CreatureInteractor & creature);
	void interact(Aphid & creature);
	void interact(Ladybug & creature);
	Ladybug(int lifespan, float startFood) : Creature(lifespan, startFood) { }
};

