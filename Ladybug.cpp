#include "Ladybug.h"
#include "ActionHandler.h"
#include "Cell.h"
#include "CreatureInteractor.h"
#include "LadybugConfiguration.h"
#include "Aphid.h"
#include <iostream>
#include <cmath>
void Ladybug::move()
{
	float gp = LadybugConfiguration::get().getDirectionChangeProbability();
	if (roll(gp))
	{
		generalDirection = (rand() % (getLocation().neighbourCount() / 2)) * 2;
	}
	float mp = LadybugConfiguration::get().getMoveProbability();
	if (roll(mp))
	{
		int offset = (rand() % 3) - 1;
		int finDir = ((generalDirection + offset) + (getLocation().neighbourCount()-1)) % (getLocation().neighbourCount()-1);
		getActionHandler().moved(*this, getLocation(), finDir);
	}
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
		if (pair.creature->getReproduced()) continue;
		pair.creature->interactWith(*this);
		break;
	}
}

void Ladybug::suicide()
{
	getActionHandler().killed(*this, getLocation(), *this);
}

float Ladybug::eat() { return 2; }

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
		getActionHandler().killed(*this, getLocation(), creature);
		addFood(creature.getNutritionalValue());
	}
}

void Ladybug::interact(Ladybug & creature)
{
	if (getPhase() != Creature::PROCREATING) return;
	if (getReproduced()) return;
	float p = LadybugConfiguration::get().getReproduceProbability();
	if (roll(p))
	{
		Creature * baby = new Ladybug((LADYBUG_LIFE / (getCounter().getLadybugs() - 1)), 0);
		getActionHandler().reproduced(*this, getLocation(), creature, *baby);
		giveBabyFood(creature, *baby, LADYBUG_START_FOOD);
	}
}

