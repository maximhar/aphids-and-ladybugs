#pragma once
#include "Creature.h"
#include "ActionHandler.h"
class Corpse :
	public Creature
{
protected:
	void suicide() { getActionHandler().killed(*this, getLocation(), *this);  }
	double eat(double initial) { return initial * 0.90; }
	double getDefaultNutritionalValue() { return 0; }
	void makeInteractWith(Creature * creature) { }
	int getDirection() { return 0; }
	double getMoveProbability() { return 0; }
	void interactWith(CreatureInteractor & creature) { creature.interact(*this); }
	void survive()
	{
		Creature::survive();
		if (getNutritionalValue() < 0.1) suicide();
	}
	char * getName() { return "Corpse"; }
	Creature * pick(CreaturePicker & picker, CreatureSorter & sorter) { return NULL; }
public:
	Corpse::Corpse(Creature * from) : Creature(1000, from->getNutritionalValue())
	{
	}
};

