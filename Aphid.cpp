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
		pair.creature->interactWith(*this);
		break;
	}
}

void Aphid::suicide()
{
	getActionHandler().killed(*this, getLocation(), *this);
}


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
		getActionHandler().reproduced(*this, getLocation(), creature, *(new Aphid(APHID_LIFE/5 + 4*((APHID_LIFE/5) / (counter.getAphids()-1)))));
		creature.setReproduced(true);
		setReproduced(true);
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
	}
}