#include "Ladybug.h"
#include "ActionHandler.h"
#include "Cell.h"
#include "CreatureInteractor.h"
#include "LadybugConfiguration.h"
#include "Aphid.h"
#include <iostream>

ActionHandler * _handler;
Cell * _location;

void Ladybug::move()
{
	int dir = (rand() % (getLocation().neighbourCount()/2)) * 2;
	getActionHandler().moved(*this, getLocation(), dir);
}

void Ladybug::kill()
{
	while (getContents().hasNext())
	{
		auto pair = getContents().next();
		if (pair.creature == this) continue;
		pair.creature->interactWith(*this);
		break;
	}
}

void Ladybug::procreate()
{
	while (getContents().hasNext())
	{
		auto pair = getContents().next();
		if (pair.creature == this) continue;
		pair.creature->interactWith(*this);
		break;
	}
}

void Ladybug::suicide()
{
	getActionHandler().killed(*this, getLocation(), *this);
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
	if (getReproduced()) return;
	float p = LadybugConfiguration::get().getReproduceProbability();
	if (roll(p))
	{
		//std::cout << "Ladybug giving birth" << std::endl;
		getActionHandler().reproduced(*this, getLocation(), creature, *(new Ladybug(LADYBUG_LIFE)));
	}
}

