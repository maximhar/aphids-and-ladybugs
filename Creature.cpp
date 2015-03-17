#include "Creature.h"
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
		interactImpl(pair.creature);
		break;
	}
}
void Creature::procreate()
{
	while (getContents().hasNext())
	{
		auto pair = getContents().next();
		if (pair.creature == this) continue;
		if (pair.creature->getReproduced()) continue;
		interactImpl(pair.creature);
		break;
	}
}

void Creature::killCreature(Creature & creature)
{
	getActionHandler().killed(*this, getLocation(), creature);
	addFood(creature.getNutritionalValue());
	creature.food = 0;
}
void Creature::makeBaby(Creature & parent, Creature & baby, double babyFood)
{
	getActionHandler().reproduced(*this, getLocation(), parent, baby);
	giveBabyFood(parent, baby, babyFood);
	parent.setReproduced(true);
	setReproduced(true);
}