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
	float food;
	float nutritionalValue;
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
	virtual void suicide() = 0;
	virtual float eat() = 0;
	virtual float getDefaultNutritionalValue() = 0;
	virtual void interactImpl(Creature * creature) = 0;
	virtual int getDirection() = 0;
	virtual float getMoveProbability() = 0;
	void addFood(float f) { food += f; }
	CreatureCounter getCounter() { return counter; }
	bool roll(float p)
	{
		float r = (rand() % 100) / 100.0f;
		return (p > r);
	}
	void giveBabyFood(Creature & otherParent, Creature & baby, float amount)
	{
		float actual = std::min(amount / 2, std::min(food, otherParent.food));
		baby.food += actual*2;
		otherParent.food -= actual;
		food -= actual;
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
	Creature(int lifespan, float startFood) : 
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
		decreaseLifespan();
		food -= eat();
		if (!isAlive() || food < 0) suicide();
	}
	virtual void interactWith(CreatureInteractor & creature) = 0;
	bool getReproduced() { return hasReproduced; }
	float getNutritionalValue() { return getDefaultNutritionalValue() + food; }
};