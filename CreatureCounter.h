#pragma once
#include "CreatureInteractor.h"
class Creature;
class Aphid;
class Ladybug;
class CreatureCounter : public CreatureInteractor
{
private:
	int ladybugs, aphids;
public:
	void interact(Ladybug & ladybug) { ladybugs++; }
	void interact(Aphid & aphid) { aphids++; }
	void reset()
	{
		aphids = ladybugs = 0;
	}
	int getAphids() { return aphids; }
	int getLadybugs() { return ladybugs; }
};