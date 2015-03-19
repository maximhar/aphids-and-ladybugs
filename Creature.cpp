#include <iostream>
#include "Creature.h"
#include "Corpse.h"
#include "ActionHandler.h"
void Creature::move()
{
	float p = getMoveProbability();
	if (roll(p))
	{
		int dir = getDirection();
		getActionHandler().moved(*this, getLocation(), dir);
	}
}
void Creature::kill()
{
	Creature * current;
	FoePicker picker;
	CreatureSorter & sorter = handler->getDeletionSorter(*location);
	while ((current = pick(picker, sorter)) != NULL)
	{
		if (current == this) continue;
		if (!handler->canChange(*current)) continue;
		makeInteractWith(current);
		break;
	}
}
void Creature::procreate()
{
	Creature * current;
	MatePicker picker;
	CreatureSorter & sorter = handler->getAdditionSorter(*location);
	while ((current = pick(picker, sorter)) != NULL)
	{
		if (current == this) continue;
		if (!handler->canChange(*current)) continue;
		if (current->hasReproduced) continue;
		makeInteractWith(current);
		break;
	}
}

void Creature::survive()
{
	lifespan--;
	food = eat(food);
	if (lifespan <= 0 || food <= 0) suicide();
}

void Creature::suicide()
{
	getActionHandler().killed(*this, getLocation(), *this);
	if(getNutritionalValue() > 0.1) 
		getActionHandler().reproduced(*this, getLocation(), *this, *(new Corpse(this)));
}

void Creature::killCreature(Creature & creature)
{
	food += creature.getNutritionalValue();
	creature.food = 0;
	getActionHandler().killed(*this, getLocation(), creature);
	hasKilled = true;
}
void Creature::makeBaby(Creature & parent, Creature & baby)
{
	getActionHandler().reproduced(*this, getLocation(), parent, baby);
	giveBabyFood(parent, baby);
	parent.hasReproduced = true;
	hasReproduced = true;
}