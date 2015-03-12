#pragma once
#include <utility>
#include <map>
#include <vector>
class Manager;
class Creature;
class Cell;
class CreatureCounter;
class ActionHandler;

class Creature 
{
private:
	
public:
	virtual void count(CreatureCounter & counter) = 0;
	virtual void update(ActionHandler & handler, Cell & location, std::pair<std::vector<Creature *>::iterator, std::vector<Creature * >::iterator> contents) = 0;
};