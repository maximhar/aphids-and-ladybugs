#pragma once
#include "Creature.h"
class Corpse :
	public Creature
{
protected:
	void suicide() { getActionHandler().killed(*this, getLocation(), *this);  }
	double eat(double initial) { return initial * 0.95; }
	double getDefaultNutritionalValue() { return 0; }
	void interactImpl(Creature * creature) { }
	int getDirection() { return 0; }
	double getMoveProbability() { return 0; }
	void interactWith(CreatureInteractor & creature) { creature.interact(*this); }
	void survive()
	{
		Creature::survive();
		if (getNutritionalValue() < 0.1) suicide();
	}
public:
	Corpse::Corpse(Creature * from) : Creature(1000, from->getNutritionalValue())
	{
	}
};

