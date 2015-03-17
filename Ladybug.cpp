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
	Creature::move();
}

int Ladybug::getDirection()
{
	int offset = (rand() % 3) - 1;
	return ((generalDirection + offset) + (getLocation().neighbourCount() - 1)) % (getLocation().neighbourCount() - 1);
}

void Ladybug::suicide() { getActionHandler().killed(*this, getLocation(), *this); }

double Ladybug::eat() { return LadybugConfiguration::get().getFoodPerTurn(); }

double Ladybug::getDefaultNutritionalValue() { return LadybugConfiguration::get().getNutritionalValue(); }

void Ladybug::interactWith(CreatureInteractor & creature) { creature.interact(*this); }

double Ladybug::getMoveProbability() { return LadybugConfiguration::get().getMoveProbability(); }

void Ladybug::interact(Aphid & creature)
{
	if (getPhase() != Creature::KILLING) return;
	float p = LadybugConfiguration::get().getKillAphidProbability();
	if (roll(p))
	{
		killCreature(creature);
	}
}

void Ladybug::interact(Ladybug & creature)
{
	if (getPhase() != Creature::PROCREATING) return;
	if (getReproduced()) return;
	float p = LadybugConfiguration::get().getReproduceProbability();
	if (roll(p))
	{
		Creature * baby = new Ladybug(LadybugConfiguration::get().getLife(), 0);
		makeBaby(creature, *baby, LadybugConfiguration::get().getStartingFood());
	}
}

