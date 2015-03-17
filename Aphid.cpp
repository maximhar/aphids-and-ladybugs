#include "Aphid.h"
#include "Cell.h"
#include "ActionHandler.h"
#include "CreatureInteractor.h"
#include "AphidConfiguration.h"
#include "Ladybug.h"
#include <cstdlib>
#include <iostream>

int Aphid::getDirection() { return rand() % getLocation().neighbourCount(); }

void Aphid::suicide() { getActionHandler().killed(*this, getLocation(), *this); }

double Aphid::eat() { return AphidConfiguration::get().getFoodPerTurn(); }

double Aphid::getDefaultNutritionalValue() { return AphidConfiguration::get().getNutritionalValue(); }

void Aphid::interactWith(CreatureInteractor & creature) { creature.interact(*this); }

double Aphid::getMoveProbability() { return AphidConfiguration::get().getMoveProbability(); }

void Aphid::interact(Aphid & creature)
{
	if (getPhase() != Creature::PROCREATING) return;
	if (getReproduced()) return;
	float p = AphidConfiguration::get().getReproduceProbability();
	if (roll(p))
	{
		Creature * baby = new Aphid(AphidConfiguration::get().getLife(), 0);
		makeBaby(creature, *baby, AphidConfiguration::get().getStartingFood());
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
		killCreature(creature);
	}
}