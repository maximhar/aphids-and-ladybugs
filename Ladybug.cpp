#include "Ladybug.h"
#include "ActionHandler.h"
#include "Cell.h"
#include "CreatureInteractor.h"
#include "LadybugConfiguration.h"
#include "Aphid.h"
#include <iostream>

ActionHandler * _handler;
Cell * _location;

void Ladybug::move(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents)
{
	Creature::move(handler, location, contents);
	int dir = (rand() % (location.neighbourCount()/2)) * 2;
	handler.moved(*this, location, dir);
}

void Ladybug::kill(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents)
{
	Creature::kill(handler, location, contents);
	while (contents->hasNext())
	{
		auto pair = contents->next();
		if (pair.creature == this) continue;
		pair.creature->interactWith(*this);
		break;
	}
}

void Ladybug::procreate(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents)
{
	Creature::procreate(handler, location, contents);
	while (contents->hasNext())
	{
		auto pair = contents->next();
		if (pair.creature == this) continue;
		pair.creature->interactWith(*this);
		break;
	}
}

void Ladybug::interactWith(CreatureInteractor & creature)
{
	creature.interact(*this);
}

void Ladybug::interact(Aphid & creature)
{
	if (getPhase() != Creature::KILLING) return;
	float p = LadybugConfiguration::get().getKillAphidProbability();
	if (roll(p))
	{
		//std::cout << "Ladybug killing aphid" << std::endl;
		getActionHandler().killed(*this, getLocation(), creature);
	}
}

void Ladybug::interact(Ladybug & creature)
{
	if (getPhase() != Creature::PROCREATING) return;
	float p = LadybugConfiguration::get().getReproduceProbability();
	if (roll(p))
	{
		//std::cout << "Ladybug giving birth" << std::endl;
		getActionHandler().reproduced(*this, getLocation(), creature, *(new Ladybug()));
	}
}