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
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>
#include <set>

class Manager : public ActionHandler
{
private:
	std::map<Cell *, std::vector<Creature *>> * cellCreaturesMap;
	std::map<Creature *, Cell *> creatureCellMap;
	std::set<Creature *> modified;
	World * world;
public:
	Manager()
	{
		SquareLoader * load = new SquareLoader();
		std::ifstream config;
		config.open("manager.txt");
		if (!config.is_open()) std::cout << "File is not open...";
		else load->load(&cellCreaturesMap, &world, config);
	}
	
	bool isModified(Creature * creature)
	{
		return(modified.count(creature) > 0);
	}

	void setModified(Creature * creature)
	{
		modified.insert(creature);
	}

	//TODO: map cell creatures to creature cell map, and make updateAll iterate creature cell

	void updateAll()
	{
		modified.clear();
		auto map = std::map<Cell *, std::vector<Creature *>>(*cellCreaturesMap);
		auto begin = map.begin();
		auto end = map.end();
		for (auto it = begin; it != end; it++)
		{
			auto & vec = it->second; 
			for (auto it2 = vec.begin(); it2 != vec.end(); it2++)
			{
				if (isModified(*it2)) 
					continue;
				(*it2)->update(*this, *it->first, std::make_pair(it->second.begin(), it->second.end()));
			}
		}
	}

	void countAll()
	{
		CreatureCounter counter;
		auto begin = cellCreaturesMap->begin();
		auto end = cellCreaturesMap->end();
		for (auto it = begin; it != end; it++)
		{
			auto vec = &it->second;
			for (auto it2 = vec->begin(); it2 != vec->end(); it2++)
			{
				(*it2)->interactWith(counter);
			}
		}
		std::cout << "Aphids: " << counter.getAphids() << ", Ladybugs: " << counter.getLadybugs() << std::endl;
	}

	void run()
	{
		while (true)
		{
			world->getPrinter().print(*cellCreaturesMap, std::cout);
			countAll();
			updateAll();
			std::this_thread::sleep_for(std::chrono::milliseconds(250));
			system("CLS");
		}
	}

	bool deleteCreature(Creature& creature, Cell& cell)
	{
		auto range = cellCreaturesMap->find(&cell);
		for (auto it = range->second.begin(); it != range->second.end(); it++)
		{
			if ((*it) == &creature)
			{
				range->second.erase(it);
				return true;
			}
		}
		return false;
	}

	void addCreature(Creature& creature, Cell& cell)
	{
		auto it = cellCreaturesMap->find(&cell);
		if (it == cellCreaturesMap->end())
		{
			it = cellCreaturesMap->insert(std::make_pair(&cell, std::vector<Creature *>())).first;
		}
		it->second.push_back(&creature);
	}

	void moved(Creature& self, Cell& location, int direction)
	{
		if (location.getNeighbour(direction) == Cell::EDGE)
			direction = (direction + location.neighbourCount() / 2) % location.neighbourCount();

		Cell * newloc;
		if ((newloc = location.getNeighbour(direction)) == Cell::EDGE)
			direction = (location.neighbourCount() - direction) % location.neighbourCount();
		newloc = location.getNeighbour(direction);
		if (newloc == Cell::EDGE) return; 

		deleteCreature(self, location);
		addCreature(self, *newloc);
	}

	void killed(Creature& self, Cell& location, Creature& victim)
	{
		bool suc = deleteCreature(victim, location);
		if(suc) setModified(&victim);
		std::cout << "Creature deleted, success " << suc << std::endl;
	}

	void reproduced(Creature& self, Cell& location, Creature& partner, Creature& offspring)
	{
		addCreature(offspring, location);
		//std::cout << "Creature added" << std::endl;
	}

	~Manager()
	{
		
		for (auto iter = cellCreaturesMap->begin(); iter != cellCreaturesMap->end(); ++iter)
		{
			for (auto it2 = iter->second.begin(); it2 != iter->second.end(); it2++)
			{
				delete (*it2);
			}
			
		}
		delete world;
	}
};