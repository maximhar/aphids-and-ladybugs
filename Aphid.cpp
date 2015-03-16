#include "Aphid.h"
#include "Cell.h"
#include "ActionHandler.h"
#include "CreatureInteractor.h"
#include "AphidConfiguration.h"
#include "Ladybug.h"
#include <cstdlib>
#include <iostream>

void Aphid::move(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents)
{
	Creature::move(handler, location, contents);
	float p = AphidConfiguration::get().getMoveProbability();
	if (roll(p))
	{
		int dir = rand() % location.neighbourCount();
		handler.moved(*this, location, dir);
	}
}

void Aphid::kill(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents)
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

void Aphid::procreate(ActionHandler & handler, Cell & location, WorldMap::CreatureIterator * contents)
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

void Aphid::interactWith(CreatureInteractor & creature)
{
	creature.interact(*this);
}

void Aphid::interact(Aphid & creature)
{
	if (getPhase() != Creature::PROCREATING) return;
	float p = AphidConfiguration::get().getReproduceProbability();
	if (roll(p))
	{
		getActionHandler().reproduced(*this, getLocation(), creature, *(new Aphid()));
	}
}

void Aphid::interact(Ladybug & creature)
{
	if (getPhase() != Creature::KILLING) return;
	float p = AphidConfiguration::get().getKillLadybugProbability();
	if (roll(p))
	{
		getActionHandler().killed(*this, getLocation(), creature);
	}
}