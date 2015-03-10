#pragma once

#include <iostream>
#include <map>
#include <utility>
#include "Creature.h"
#include "World.h"
#include "SquareWorld.h"
#include "SquareCell.h"
class Manager
{
private:
	std::multimap<Cell *, Creature *> * creatures;
	World * world;
public:
	Manager() : world(new SquareWorld(10, 8)), creatures(new std::multimap<Cell *, Creature *>())
	{
		creatures->insert(std::make_pair(&world->getOrigin(), new Creature()));
		creatures->insert(std::make_pair(world->getOrigin().getNeighbour(SquareCell::BOTTOM), new Creature()));
	}

	void run()
	{
		world->getPrinter().print(*creatures, std::cout);
	}

	~Manager()
	{
		
		for (auto iter = creatures->begin(); iter != creatures->end(); ++iter)
		{
			delete iter->second;
		}
		delete world;
	}
};