#include "Aphid.h"
#include "Cell.h"
#include "ActionHandler.h"
#include "CreatureInteractor.h"
#include "AphidConfiguration.h"
#include "Ladybug.h"
#include "Corpse.h"
#include "FoePicker.h"
#include "MatePicker.h"
#include <cstdlib>
#include <iostream>

int Aphid::getDirection() { return rand() % getLocation().neighbourCount(); }

double Aphid::eat(double initial) { return initial - AphidConfiguration::get().getFoodPerTurn(); }

double Aphid::getDefaultNutritionalValue() { return AphidConfiguration::get().getNutritionalValue(); }

void Aphid::interactWith(CreatureInteractor & creature) { creature.interact(*this); }

double Aphid::getMoveProbability() { return AphidConfiguration::get().getMoveProbability(); }

Creature * Aphid::pick(CreaturePicker & picker, CreatureSorter & sorter) 
{
	return picker.pick(sorter, *this);
}

void Aphid::interact(Aphid & creature)
{
	if (getPhase() != Creature::PROCREATING) return;
	float p = AphidConfiguration::get().getReproduceProbability();
	if (roll(p))
	{
		Creature * baby = new Aphid(AphidConfiguration::get().getLife(), 0);
		makeBaby(creature, *baby);
	}
}

void Aphid::interact(Ladybug & creature)
{
	if (getPhase() != Creature::KILLING) return;
	float p = AphidConfiguration::get().getKillLadybugProbability();
	float g = AphidConfiguration::get().getKillLadybugGroupProbability();
	CreatureCounter counter = getActionHandler().getCounter(getLocation());
	float gn = (counter.getAphids() - 1) * g;
	if (roll(p + gn))
	{
		killCreature(creature);
	}
}

void Aphid::interact(Corpse & creature)
{
	if (getPhase() != Creature::KILLING) return;
	killCreature(creature);
}