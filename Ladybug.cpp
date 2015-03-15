#include "Ladybug.h"
#include "ActionHandler.h"
#include "Cell.h"
#include "CreatureInteractor.h"
#include "LadybugConfiguration.h"
#include "Aphid.h"
#include <iostream>

ActionHandler * _handler;
Cell * _location;

void Ladybug::update(ActionHandler & handler, Cell & location, std::pair<std::vector<Creature *>::iterator, std::vector<Creature * >::iterator> contents)
{
	_handler = &handler;
	_location = &location;
	setPhase(Creature::MOVING);
	int dir = (rand() % (location.neighbourCount()/2)) * 2;
	handler.moved(*this, location, dir);
	setPhase(Creature::KILLING);
	for (auto it = contents.first; it != contents.second; ++it)
	{
		if (*it == this) continue;
		(*it)->interactWith(*this);
		break;
	}
	setPhase(Creature::PROCREATING);
	for (auto it = contents.first; it != contents.second; ++it)
	{
		if (*it == this) continue;
		(*it)->interactWith(*this);
		break;
	}
}

void Ladybug::interactWith(CreatureInteractor & creature)
{
	creature.interact(*this);
}

void Ladybug::interact(Aphid & creature)
{
	if (getPhase() != Creature::KILLING) return;
	float p = LadybugConfiguration::get().getKillAphidProbability();
	float r = (rand() % 100) / 100.0f;
	if (p > r)
	{
		//std::cout << "Ladybug killing aphid" << std::endl;
		_handler->killed(*this, *_location, creature);
	}
}

void Ladybug::interact(Ladybug & creature)
{
	if (getPhase() != Creature::PROCREATING) return;
	float p = LadybugConfiguration::get().getReproduceProbability();
	float r = (rand() % 100) / 100.0f;
	if (p > r)
	{
		//std::cout << "Ladybug giving birth" << std::endl;
		_handler->reproduced(*this, *_location, creature, *(new Ladybug()));
	}
}