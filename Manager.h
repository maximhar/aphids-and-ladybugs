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

class Manager
{
private:
	std::multimap<Cell *, Creature *> * creatures;
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