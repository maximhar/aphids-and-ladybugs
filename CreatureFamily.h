#pragma once
class Creature;
class Cell;
struct CreatureFamily
{
	Creature * child;
	Creature * parent1;
	Creature * parent2;
	Cell * location;
	CreatureFamily(Cell * loc, Creature * c, Creature * p1, Creature * p2)
		: location(loc), child(c), parent1(p1), parent2(p2)
	{}
};