#pragma once
#include "CreatureCellPair.h"
class CreatureIterator
{
public:
	virtual bool hasNext() = 0;
	virtual CreatureCellPair next() = 0;
	virtual void reset() = 0;
	virtual CreatureIterator * copy() = 0;
};