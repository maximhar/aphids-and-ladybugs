#pragma once
#include "Creature.h"
#include "CreatureCounter.h"
#include "CreatureInteractor.h"
class Aphid : public Creature, public CreatureInteractor
{
protected:
	void suicide();
	double eat();
	double getDefaultNutritionalValue();
	void interactImpl(Creature * creature) { creature->interactWith(*this); }
	int getDirection();
	double getMoveProbability();
public:
	void interactWith(CreatureInteractor & creature);
	void interact(Aphid & creature);
	void interact(Ladybug & creature);
	Aphid(int lifespan, float startFood) : Creature(lifespan, startFood) { }
};

