#include "Aphid.h"
#include "Cell.h"
#include "ActionHandler.h"
#include "CreatureInteractor.h"
#include <cstdlib>
#include <iostream>


void Aphid::update(ActionHandler & handler, Cell & location, std::pair<std::vector<Creature *>::iterator, std::vector<Creature * >::iterator> contents)
{
	int dir = rand() % location.neighbourCount();
	handler.moved(*this, location, dir);
	for (auto it = contents.first; it != contents.second; ++it)
	{
		if (*it == this) continue;
		(*it)->interactWith(*this);
	}
}

void Aphid::interactWith(CreatureInteractor & creature)
{
	creature.interact(*this);
}

void Aphid::interact(Aphid & creature)
{
	std::cout << "Aphid with aphid" << std::endl;
}

void Aphid::interact(Ladybug & creature)
{
	std::cout << "Aphid with ladybug" << std::endl;
}