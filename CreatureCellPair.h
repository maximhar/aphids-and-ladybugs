#pragma once
class Cell;
class Creature;
struct CreatureCellPair
{
	Cell * cell;
	Creature * creature;
	CreatureCellPair(Cell * ce, Creature * cr)
		: cell(ce), creature(cr)
	{}
};