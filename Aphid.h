#pragma once
#include "Creature.h"
#include "CreatureCounter.h"
#include "CreatureInteractor.h"
class Aphid : public Creature, public CreatureInteractor
{
protected:
	double eat(double initial);
	double getDefaultNutritionalValue();
	void makeInteractWith(Creature * creature) { creature->interactWith(*this); }
	int getDirection();
	double getMoveProbability();
	char * getName() { return "Aphid"; }
	Creature * pick(CreaturePicker & picker, CreatureSorter & sorter);
public:
	void interactWith(CreatureInteractor & creature);
	void interact(Aphid & creature);
	void interact(Ladybug & creature);
	void interact(Corpse & creature);
	Aphid(int lifespan, float startFood) : Creature(lifespan, startFood) { }
};

