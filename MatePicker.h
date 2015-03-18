#pragma once
#include "CreaturePicker.h"
class Creature;
class CreatureSorter;
class Aphid;
class Ladybug;
class MatePicker : public CreaturePicker
{
public:
	virtual Creature * pick(CreatureSorter & sorter, Aphid & subject);
	virtual Creature * pick(CreatureSorter & sorter, Ladybug & subject);
};