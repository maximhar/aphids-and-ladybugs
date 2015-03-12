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
#include <chrono>
#include <thread>
#include <vector>
#include <cmath>

class Manager : public ActionHandler
{
private:
	std::map<Cell *, std::vector<Creature *>> * creatures;
	World * world;
public:
	Manager()
	{
		SquareLoader * load = new SquareLoader();
		std::ifstream config;
		config.open("manager.txt");
		if (!config.is_open()) std::cout << "File is not open...";
		else load->load(&creatures, &world, config);
	}

	void updateAll()
	{
		auto map = std::map<Cell *, std::vector<Creature *>>(*creatures);
		auto begin = map.begin();
		auto end = map.end();
		for (auto it = begin; it != end; it++)
		{
			auto vec = &it->second; 
			for (auto it2 = vec->begin(); it2 != vec->end(); it2++)
			{
				(*it2)->update(*this, *it->first, std::make_pair(it->second.begin(), it->second.end()));
			}
		}
	}

	void run()
	{
		while (true)
		{
			world->getPrinter().print(*creatures, std::cout);
			updateAll();
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
			system("CLS");
		}
	}

	bool deleteCreature(Creature& creature, Cell& cell)
	{
		auto range = creatures->find(&cell);
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
		auto it = creatures->find(&cell);
		if (it == creatures->end())
		{
			it = creatures->insert(std::make_pair(&cell, std::vector<Creature *>())).first;
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

	}
	void reproduced(Creature& self, Cell& location, Creature& partner)
	{

	}

	~Manager()
	{
		
		for (auto iter = creatures->begin(); iter != creatures->end(); ++iter)
		{
			for (auto it2 = iter->second.begin(); it2 != iter->second.end(); it2++)
			{
				delete (*it2);
			}
			
		}
		delete world;
	}
};