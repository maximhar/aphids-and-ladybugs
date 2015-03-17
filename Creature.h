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
	int lifespan;
	double food;
protected:
	enum Phase { MOVING, KILLING, PROCREATING, SURVIVING };
	Phase getPhase() { return phase; }
	void setPhase(Phase phase) { this->phase = phase; }
	ActionHandler & getActionHandler() { return *handler; }
	Cell & getLocation() { return *location; }
	WorldMap::CreatureIterator & getContents() { return *contents; }
	void setReproduced(bool r) { hasReproduced = r; }
	void decreaseLifespan() { lifespan--; }
	bool isAlive() { return lifespan > 0; }
	virtual void move();
	virtual void kill();
	virtual void procreate();
	virtual void survive();
	virtual void suicide() = 0;
	virtual double eat(double initial) = 0;
	virtual double getDefaultNutritionalValue() = 0;
	virtual void interactImpl(Creature * creature) = 0;
	virtual int getDirection() = 0;
	virtual double getMoveProbability() = 0;
	void addFood(double f) { food += f; }
	void killCreature(Creature & creature);
	void makeBaby(Creature & parent, Creature & baby, double babyFood);
	CreatureCounter getCounter() { return counter; }
	bool roll(float p)
	{
		float r = (rand() % 100) / 100.0f;
		return (p > r);
	}
	void giveBabyFood(Creature & otherParent, Creature & baby, double amount)
	{
		double actual1 = std::min(amount / 2, food / 1.5);
		double actual2 = std::min(amount / 2, otherParent.food / 1.5);
		baby.food += actual1;
		baby.food += actual2;
		otherParent.food -= actual2;
		food -= actual1;
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
		setPhase(Creature::MOVING);
		initialiseState(handler, location, contents, cellCounter);
		setReproduced(false);
		move();
	}
	void kill(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		setPhase(Creature::KILLING);
		initialiseState(handler, location, contents, cellCounter);
		kill();
	}
	void procreate(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		setPhase(Creature::PROCREATING);
		initialiseState(handler, location, contents, cellCounter);
		if (getReproduced()) return;
		procreate();
	}
	virtual void survive(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		setPhase(Creature::SURVIVING);
		initialiseState(handler, location, contents, cellCounter);
		survive();
	}
	virtual void interactWith(CreatureInteractor & creature) = 0;
	bool getReproduced() { return hasReproduced; }
	double getNutritionalValue() { return getDefaultNutritionalValue() + food; }
};