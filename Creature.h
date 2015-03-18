#pragma once
#include <utility>
#include <map>
#include <vector>
#include <set>
#include <cmath>
#include "WorldMap.h"
#include "CreatureCounter.h"
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
	WorldMap::CreatureIterator * contents;
	CreatureCounter counter;
	bool hasReproduced;
	bool hasKilled;
	int lifespan;
	double food;
protected:
	enum Phase { MOVING, KILLING, PROCREATING, SURVIVING };
	Phase getPhase() { return phase; }
	ActionHandler & getActionHandler() { return *handler; }
	Cell & getLocation() { return *location; }
	WorldMap::CreatureIterator & getContents() { return *contents; }
	void makeBaby(Creature & parent, Creature & baby);
	virtual void move();
	virtual void kill();
	virtual void procreate();
	virtual void survive();
	virtual void suicide();
	virtual double eat(double initial) = 0;
	virtual double getDefaultNutritionalValue() = 0;
	virtual void makeInteractWith(Creature * creature) = 0;
	virtual int getDirection() = 0;
	virtual double getMoveProbability() = 0;
	void killCreature(Creature & creature);
	CreatureCounter getCounter() { return counter; }
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
	void initialiseState(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		this->handler = &handler;
		this->location = &location;
		this->contents = contents;
		this->counter = cellCounter;
	}
private:
	Phase phase;
public:
	Creature(int lifespan, double startFood) :
		hasReproduced(false), lifespan(lifespan), food(startFood)
	{
	}
	void move(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		phase = Creature::MOVING;
		initialiseState(handler, location, contents, cellCounter);
		hasReproduced = false;
		hasKilled = false;
		move();
	}
	void kill(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		phase = Creature::KILLING;
		initialiseState(handler, location, contents, cellCounter);
		kill();
	}
	void procreate(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		phase = Creature::PROCREATING;
		initialiseState(handler, location, contents, cellCounter);
		if (hasReproduced) return;
		procreate();
	}
	virtual void survive(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		phase = Creature::SURVIVING;
		initialiseState(handler, location, contents, cellCounter);
		survive();
	}
	virtual void interactWith(CreatureInteractor & creature) = 0;
	double getNutritionalValue() { return getDefaultNutritionalValue() + food; }
};