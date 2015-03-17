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
#include <iomanip>

class Manager : public ActionHandler
{
private:
	World * world;
	WorldMap * worldMap;
	int turn;
	std::ofstream os;
public:
	Manager() : worldMap(new WorldMap()), turn(0)
	{
		Loader * loader = new SquareLoader();
		std::ifstream config("manager.txt");
		os = std::ofstream("graph.csv");
		if (!config.is_open()) std::cout << "File is not open...";
		else
		{
			world = loader->load(worldMap, config);
			worldMap->flush();
		}
	}
	
	void updateAll()
	{
		WorldMap::CreatureIterator * it = worldMap->allCreatures();
		while (it->hasNext())
		{	
			auto pair = it->next();
			auto iter = worldMap->creaturesInCell(*pair.cell);
			pair.creature->move(*this, *pair.cell, iter, worldMap->getCounterForCell(*pair.cell));
			delete iter;
		}
		delete it;
		worldMap->flush();
		it = worldMap->allCreatures();
		while (it->hasNext())
		{
			auto pair = it->next();
			auto iter = worldMap->creaturesInCell(*pair.cell);
			pair.creature->kill(*this, *pair.cell, iter, worldMap->getCounterForCell(*pair.cell));
			delete iter;
		}
		delete it;
		worldMap->flush();
		it = worldMap->allCreatures();
		while (it->hasNext())
		{
			auto pair = it->next();
			auto iter = worldMap->creaturesInCell(*pair.cell);
			pair.creature->procreate(*this, *pair.cell, iter, worldMap->getCounterForCell(*pair.cell));
			delete iter;
		}
		worldMap->flush();
		it = worldMap->allCreatures();
		while (it->hasNext())
		{
			auto pair = it->next();
			auto iter = worldMap->creaturesInCell(*pair.cell);
			pair.creature->survive(*this, *pair.cell, iter, worldMap->getCounterForCell(*pair.cell));
			delete iter;
		}
		worldMap->flush();
		delete it;
	}

	bool countAll()
	{
		turn++;
		CreatureCounter counter = worldMap->getTotalsCounter();
		auto it = worldMap->allCreatures();
		double totalFood = 0;
		while (it->hasNext())
		{
			totalFood += it->next().creature->getNutritionalValue();
		}
		std::cout << "Aphids: " << counter.getAphids() << ", Ladybugs: " << counter.getLadybugs() << " Food: " << std::showpoint << std::fixed << std::setw(2) << totalFood << std::endl;
		std::cout << "Turn: " << turn << std::endl;
		os << counter.getAphids() << "," << counter.getLadybugs() << "," << std::showpoint << std::fixed << std::setw(2) << totalFood/1000 << std::endl;
		os.flush();
		return counter.getAphids() > 0 || counter.getLadybugs() > 0;
	}

	void run()
	{
		while (true)
		{
			//world->getPrinter().print(*worldMap, std::cout);
			if (!countAll()) return;
			updateAll();
			//std::this_thread::sleep_for(std::chrono::milliseconds(200));
			//std::cin.get();
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
	}

	void killed(Creature& self, Cell& location, Creature& victim)
	{
		worldMap->deleteCreature(victim);
	}

	void reproduced(Creature& self, Cell& location, Creature& partner, Creature& offspring)
	{
		worldMap->addCreature(offspring, location);
	}

	~Manager()
	{
		delete worldMap;
		delete world;
	}
};