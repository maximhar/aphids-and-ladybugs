#pragma once

#include <iostream>
#include <utility>
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <cmath>
#include <iomanip>
#include "Creature.h"
#include "World.h"
#include "SquareWorld.h"
#include "SquareCell.h"
#include "SquareLoader.h"
#include "ActionHandler.h"
#include "CreatureCounter.h"
#include "WorldMap.h"
#include "AphidConfiguration.h"
#include "LadybugConfiguration.h"
#include "SorterManager.h"
#include "CreatureIterator.h"
#include <time.h>
class Manager : public ActionHandler
{
private:
	World * world;
	WorldMap * worldMap;
	int turn;
	time_t lastt;
	std::ofstream os;
public:
	Manager() : worldMap(new WorldMap()), turn(0)
	{

	}
	
	void updateAll()
	{
		time_t t = clock();
		CreatureIterator * it = worldMap->allCreatures();
		while (it->hasNext())
		{	
			auto pair = it->next();
			pair.creature->move(*this, *pair.cell);
		}
		delete it;
		worldMap->flush();
		it = worldMap->allCreatures();
		while (it->hasNext())
		{
			auto pair = it->next();
			pair.creature->kill(*this, *pair.cell);
		}
		worldMap->flush();
		delete it;
		it = worldMap->allCreatures();
		while (it->hasNext())
		{
			auto pair = it->next();
			pair.creature->procreate(*this, *pair.cell);
		}
		worldMap->flush();
		delete it;
		it = worldMap->allCreatures();
		while (it->hasNext())
		{
			auto pair = it->next();
			pair.creature->survive(*this, *pair.cell);
		}
		worldMap->flush();
		delete it;
		lastt = clock() - t;
	}

	bool countAll()
	{
		turn++;
		CreatureCounter counter = worldMap->getTotalsCounter();
		std::cout << "Aphids: " << counter.getAphids() << ", Ladybugs: " << counter.getLadybugs() << ", Corpses: " << counter.getCorpses() << std::endl;
		std::cout << "Turn: " << turn << std::endl;
		//os << counter.getAphids() << "," << counter.getLadybugs() << "," << counter.getCorpses() << "," << std::showpoint << std::fixed << std::setw(2) << totalFood / 100 << std::endl;
		os << counter.getAphids() + counter.getLadybugs() + counter.getCorpses() << "," << (((float)lastt / CLOCKS_PER_SEC) * 1000) << std::endl;
		return counter.getAphids() > 0 || counter.getLadybugs() > 0;
	}

	void run()
	{
		Loader * loader = new SquareLoader();
		std::ifstream config("manager.txt");
		os = std::ofstream("graph.csv");
		if (!os.is_open()) std::cout << "Graph file is not open...";
		if (!config.is_open()) std::cout << "World config is not open...";
		else
		{
			world = loader->load(worldMap, config);
			worldMap->flush();
		}

		AphidConfiguration::get().printConfiguration();
		LadybugConfiguration::get().printConfiguration();
		std::cin.get();
		while (true)
		{
			updateAll();
			//world->getPrinter().print(*worldMap, std::cout);
			if (!countAll()) return;
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
		worldMap->addCreature(offspring, self, partner, location);
	}

	CreatureCounter getCounter(Cell & loc)
	{
		return worldMap->getCounterForCell(loc);
	}

	CreatureSorter & getDeletionSorter(Cell & loc)
	{
		CreatureSorter & sorter = worldMap->getDeletionSorterForCell(loc);
		sorter.begin();
		return sorter;
	}

	CreatureSorter & getAdditionSorter(Cell & loc)
	{
		CreatureSorter & sorter = worldMap->getAdditionSorterForCell(loc);
		sorter.begin();
		return sorter;
	}

	bool canChange(Creature & creature)
	{
		return !worldMap->changePending(creature);
	}

	~Manager()
	{
		delete worldMap;
		delete world;
	}
};