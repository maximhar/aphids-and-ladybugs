#include "Ladybug.h"
#include "ActionHandler.h"
#include "Cell.h"
#include <iostream>

void Ladybug::update(ActionHandler & handler, Cell & location, std::pair<std::vector<Creature *>::iterator, std::vector<Creature * >::iterator> contents)
{
	int dir = (rand() % (location.neighbourCount()/2)) * 2;
	handler.moved(*this, location, dir);
	for (auto it = contents.first; it != contents.second; ++it)
	{
		(*it)->interactWith(*this);
	}
}

void Ladybug::interactWith(Creature & creature)
{
	if (&creature != this) creature.interact(*this);
}

void Ladybug::interact(Aphid & creature)
{
	std::cout << "Ladybug with aphid" << std::endl;
}

void Ladybug::interact(Ladybug & creature)
{
	std::cout << "Ladybug with ladybug" << std::endl;
}