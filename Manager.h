#pragma once

#include <iostream>
#include <map>
#include <utility>
#include <fstream>
#include <iostream>
#include "Creature.h"
#include "World.h"
#include "SquareWorld.h"
#include "SquareCell.h"
#include "SquareLoader.h"
#include "ActionHandler.h"
#include "CreatureCounter.h"
#include "WorldMap.h"
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include <set>

class Manager : public ActionHandler
{
private:
	World * world;
	WorldMap * worldMap;
public:
	Manager()
	{
		Loader * loader = new SquareLoader();
		worldMap = new WorldMap();
		std::ifstream config("manager.txt");
		if (!config.is_open()) std::cout << "File is not open...";
		else
		{
			world = loader->load(worldMap, config);
		}
	}
	
	void updateAll()
	{
		WorldMap::CreatureIterator * it = worldMap->allCreatures();
		while (it->hasNext())
		{	
			auto pair = it->next();
			auto iter = worldMap->creaturesInCell(*pair.cell);
			pair.creature->move(*this, *pair.cell, iter);
			delete iter;
		}
		delete it;
		worldMap->flush();
		it = worldMap->allCreatures();
		while (it->hasNext())
		{
			auto pair = it->next();
			auto iter = worldMap->creaturesInCell(*pair.cell);
			pair.creature->kill(*this, *pair.cell, iter);
			delete iter;
		}
		delete it;
		it = worldMap->allCreatures();
		while (it->hasNext())
		{
			auto pair = it->next();
			auto iter = worldMap->creaturesInCell(*pair.cell);
			pair.creature->procreate(*this, *pair.cell, iter);
			delete iter;
		}
		worldMap->flush();
		delete it;
	}

	void countAll()
	{
		CreatureCounter counter;
		WorldMap::CreatureIterator *  it = worldMap->allCreatures();
		while (it->hasNext())
		{
			auto pair = it->next();
			pair.creature->interactWith(counter);
		}
		std::cout << "Aphids: " << counter.getAphids() << ", Ladybugs: " << counter.getLadybugs() << std::endl;
	}

	void run()
	{
		while (true)
		{
			world->getPrinter().print(*worldMap, std::cout);
			countAll();
			updateAll();
			std::this_thread::sleep_for(std::chrono::milliseconds(200));
			//system("CLS");
		}
	}

	void moved(Creature& self, Cell& location, int direction)
	{
		Cell * loc = &location;
		if (loc->getNeighbour(direction) == Cell::EDGE)
			direction = (direction + loc->neighbourCount() / 2) % loc->neighbourCount();

		if (loc->getNeighbour(direction) == Cell::EDGE)
			direction = (loc->neighbourCount() - direction) % loc->neighbourCount();

		if (loc->getNeighbour(direction) == Cell::EDGE)
			return;

		loc = loc->getNeighbour(direction);
		worldMap->moveCreature(self, *loc);
		//std::cout << "Creature moved" << std::endl;
	}

	void killed(Creature& self, Cell& location, Creature& victim)
	{
		worldMap->deleteCreature(victim);
		std::cout << "Creature deleted" << std::endl;
	}

	void reproduced(Creature& self, Cell& location, Creature& partner, Creature& offspring)
	{
		worldMap->addCreature(offspring, location);
		//std::cout << "Creature added" << std::endl;
	}

	~Manager()
	{
		delete worldMap;
		delete world;
	}
};