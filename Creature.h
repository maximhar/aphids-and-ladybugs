#pragma once
#include <utility>
#include <map>
#include <vector>
class Manager;
class Aphid;
class Ladybug;
class Creature;
class Cell;
class ActionHandler;
class CreatureInteractor;

class Creature 
{
protected:
	enum Phase { MOVING, KILLING, PROCREATING };
	Phase getPhase() { return phase; }
	void setPhase(Phase phase) { this->phase = phase; }
private:
	Phase phase;
public:
	virtual void update(ActionHandler & handler, Cell & location, std::pair<std::vector<Creature *>::iterator, std::vector<Creature * >::iterator> contents) = 0;
	virtual void interactWith(CreatureInteractor & creature) = 0;
};