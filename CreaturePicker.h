#pragma once
#include "CreatureSorter.h"
class Creature;
class CreaturePicker
{
public:
	virtual Creature * pick(CreatureSorter & sorter, Aphid & subject) = 0;
	virtual Creature * pick(CreatureSorter & sorter, Ladybug & subject) = 0;
};