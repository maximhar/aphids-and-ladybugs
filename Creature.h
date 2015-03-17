#pragma once
#include <utility>
#include <map>
#include <vector>
#include <set>
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
	bool hasReproduced;
	int lifespan;
	CreatureCounter counter;
protected:
	enum Phase { MOVING, KILLING, PROCREATING, SURVIVING };
	Phase getPhase() { return phase; }
	void setPhase(Phase phase) { this->phase = phase; }
	ActionHandler & getActionHandler() { return *handler; }
	Cell & getLocation() { return *location; }
	WorldMap::CreatureIterator & getContents() { return *contents; }
	void setReproduced(bool r) { hasReproduced = r; }
	bool getReproduced() { return hasReproduced; }
	void decreaseLifespan() { lifespan--; }
	bool isAlive() { return lifespan > 0; }
	bool roll(float p)
	{
		float r = (rand() % 100) / 100.0f;
		return (p > r);
	}
	virtual void move() = 0;
	virtual void kill() = 0;
	virtual void procreate() = 0;
	virtual void suicide() = 0;
	CreatureCounter getCounter() { return counter; }
private:
	Phase phase;
public:
	Creature(int lifespan) : hasReproduced(false), lifespan(lifespan)
	{
	}
	void move(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		setPhase(Creature::MOVING);
		this->handler = &handler;
		this->location = &location;
		this->contents = contents;
		this->counter = cellCounter;
		setReproduced(false);
		move();
	}
	void kill(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		setPhase(Creature::KILLING);
		this->handler = &handler;
		this->location = &location;
		this->contents = contents;
		this->counter = cellCounter;
		kill();
	}
	void procreate(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		setPhase(Creature::PROCREATING);
		this->handler = &handler;
		this->location = &location;
		this->contents = contents;
		this->counter = cellCounter;
		if (getReproduced()) return;
		procreate();
	}
	virtual void survive(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents, CreatureCounter cellCounter)
	{
		setPhase(Creature::SURVIVING);
		this->handler = &handler;
		this->location = &location;
		this->contents = contents;
		this->counter = cellCounter;
		decreaseLifespan();
		if (!isAlive()) suicide();
	}
	virtual void interactWith(CreatureInteractor & creature) = 0;

};