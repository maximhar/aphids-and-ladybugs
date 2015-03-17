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

float Ladybug::eat() { return LadybugConfiguration::get().getFoodPerTurn(); }

float Ladybug::getDefaultNutritionalValue() { return LadybugConfiguration::get().getNutritionalValue(); }

void Ladybug::interactWith(CreatureInteractor & creature) { creature.interact(*this); }

float Ladybug::getMoveProbability() { return LadybugConfiguration::get().getMoveProbability(); }

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
		Creature * baby = new Ladybug((LadybugConfiguration::get().getLife() / (getCounter().getLadybugs() - 1)), 0);
		getActionHandler().reproduced(*this, getLocation(), creature, *baby);
		giveBabyFood(creature, *baby, LadybugConfiguration::get().getStartingFood());
	}
}

