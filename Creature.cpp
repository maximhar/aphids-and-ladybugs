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
	while (getContents().hasNext())
	{
		auto pair = getContents().next();
		if (pair.creature == this) continue;
		if (!handler->canChange(*pair.creature)) continue;
		makeInteractWith(pair.creature);
		if (hasKilled) break;
	}
}
void Creature::procreate()
{
	while (getContents().hasNext())
	{
		auto pair = getContents().next();
		if (pair.creature == this) continue;
		if (pair.creature->hasReproduced) continue;
		makeInteractWith(pair.creature);
		if (hasReproduced) break;
	}
}

void Creature::survive()
{
	lifespan--;
	food = eat(food);
	if (lifespan < 0 || food < 0) suicide();
}

void Creature::suicide()
{
	getActionHandler().killed(*this, getLocation(), *this);
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