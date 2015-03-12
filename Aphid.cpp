#include "Aphid.h"
#include "Cell.h"
#include "ActionHandler.h"
#include <cstdlib>


void Aphid::update(ActionHandler & handler, Cell & location, std::pair<std::vector<Creature *>::iterator, std::vector<Creature * >::iterator> contents)
{
	int dir = rand() % location.neighbourCount();
	handler.moved(*this, location, dir);
}