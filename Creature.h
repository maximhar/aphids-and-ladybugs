#pragma once
#include <utility>
#include <map>
#include <vector>
#include <set>
#include "WorldMap.h"
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
protected:
	enum Phase { MOVING, KILLING, PROCREATING };
	Phase getPhase() { return phase; }
	ActionHandler & getActionHandler() { return *handler; }
	Cell & getLocation() { return *location; }
	WorldMap::CreatureIterator & getContents() { return *contents; }
	void setPhase(Phase phase) { this->phase = phase; }
	bool roll(float p)
	{
		float r = (rand() % 100) / 100.0f;
		return (p > r);
	}
private:
	Phase phase;
public:
	virtual void move(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents)
	{
		setPhase(Creature::MOVING);
		this->handler = &handler;
		this->location = &location;
		this->contents = contents;
	}
	virtual void kill(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents)
	{
		setPhase(Creature::KILLING);
		this->handler = &handler;
		this->location = &location;
		this->contents = contents;
	}
	virtual void procreate(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents)
	{
		setPhase(Creature::PROCREATING);
		this->handler = &handler;
		this->location = &location;
		this->contents = contents;
	}
	virtual void interactWith(CreatureInteractor & creature) = 0;
};