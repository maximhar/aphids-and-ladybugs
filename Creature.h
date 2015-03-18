#pragma once
#include <utility>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include "WorldMap.h"
#include "CreatureCounter.h"
#include "CreaturePicker.h"
#include "ActionHandler.h"
#include "CreaturePicker.h"
#include "FoePicker.h"
#include "MatePicker.h"
class Manager;
class Aphid;
class Ladybug;
class Creature;
class Cell;
class ActionHandler;
class CreatureInteractor;

class Creature 
{
private:
	ActionHandler * handler;
	Cell * location;
	bool hasReproduced;
	bool hasKilled;
	int lifespan;
	double food;
protected:
	enum Phase { MOVING, KILLING, PROCREATING, SURVIVING };
	Phase getPhase() { return phase; }
	ActionHandler & getActionHandler() { return *handler; }
	Cell & getLocation() { return *location; }
	void makeBaby(Creature & parent, Creature & baby);
	virtual void move();
	virtual void kill();
	virtual void procreate();
	virtual void survive();
	virtual void suicide();
	virtual Creature * pick(CreaturePicker & picker, CreatureSorter & sorter) = 0;
	virtual double eat(double initial) = 0;
	virtual double getDefaultNutritionalValue() = 0;
	virtual void makeInteractWith(Creature * creature) = 0;
	virtual int getDirection() = 0;
	virtual double getMoveProbability() = 0;
	virtual char * getName() = 0;
	void killCreature(Creature & creature);
	bool roll(float p)
	{
		float r = (rand() % 100) / 100.0f;
		return (p > r);
	}
	void giveBabyFood(Creature & otherParent, Creature & baby)
	{
		double food1 = food / 1.5;
		double food2 = otherParent.food / 1.5;
		baby.food += food1;
		baby.food += food2;
		otherParent.food -= food2;
		food -= food1;
	}
	void initialiseState(ActionHandler & handler, Cell & location)
	{
		this->handler = &handler;
		this->location = &location;
	}
private:
	Phase phase;
public:
	Creature(int lifespan, double startFood) :
		hasReproduced(false), lifespan(lifespan), food(startFood)
	{
	}
	void move(ActionHandler & handler, Cell & location)
	{
		phase = Creature::MOVING;
		if (!handler.canChange(*this)) return;
		initialiseState(handler, location);
		hasReproduced = false;
		hasKilled = false;
		move();
	}
	void kill(ActionHandler & handler, Cell & location)
	{
		phase = Creature::KILLING;
		if (!handler.canChange(*this)) return; 
		initialiseState(handler, location);
		kill();
	}
	void procreate(ActionHandler & handler, Cell & location)
	{
		phase = Creature::PROCREATING;
		initialiseState(handler, location);
		if (hasReproduced) return;
		procreate();
	}
	virtual void survive(ActionHandler & handler, Cell & location)
	{
		phase = Creature::SURVIVING;
		initialiseState(handler, location);
		survive();
	}
	virtual void interactWith(CreatureInteractor & creature) = 0;
	double getNutritionalValue() { return getDefaultNutritionalValue() + food; }
};