#include "Aphid.h"
#include "Cell.h"
#include "ActionHandler.h"
#include "CreatureInteractor.h"
#include "AphidConfiguration.h"
#include "Ladybug.h"
#include <cstdlib>
#include <iostream>

void Aphid::move()
{
	float p = AphidConfiguration::get().getMoveProbability();
	if (roll(p))
	{
		int dir = rand() % getLocation().neighbourCount();
		getActionHandler().moved(*this, getLocation(), dir);
	}
}

void Aphid::kill()
{
	while (getContents().hasNext())
	{
		auto pair = getContents().next();
		if (pair.creature == this) continue;
		pair.creature->interactWith(*this);
		break;
	}
}

void Aphid::procreate()
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

void Aphid::suicide()
{
	getActionHandler().killed(*this, getLocation(), *this);
}


float Aphid::eat() { return 1; }

void Aphid::interactWith(CreatureInteractor & creature)
{
	creature.interact(*this);
}

void Aphid::interact(Aphid & creature)
{
	if (getPhase() != Creature::PROCREATING) return;
	if (getReproduced()) return;
	float p = AphidConfiguration::get().getReproduceProbability();
	if (roll(p))
	{
		CreatureCounter counter = getCounter();
		Creature * baby = new Aphid((APHID_LIFE / (counter.getAphids() - 1)), 0);
		getActionHandler().reproduced(*this, getLocation(), creature, *baby);
		creature.setReproduced(true);
		setReproduced(true);
		giveBabyFood(creature, *baby, APHID_START_FOOD);
	}
}

void Aphid::interact(Ladybug & creature)
{
	if (getPhase() != Creature::KILLING) return;
	float p = AphidConfiguration::get().getKillLadybugProbability();
	float g = AphidConfiguration::get().getKillLadybugGroupProbability();
	CreatureCounter counter = getCounter();
	float gn = (counter.getAphids() - 1) * g;
	if (roll(p + gn))
	{
		getActionHandler().killed(*this, getLocation(), creature);
		addFood(creature.getNutritionalValue());
	}
}