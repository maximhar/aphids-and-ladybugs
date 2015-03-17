#pragma once
#include "CreatureInteractor.h"
class Creature;
class Aphid;
class Ladybug;
class CreatureCounter : public CreatureInteractor
{
private:
	int ladybugs, aphids;
	bool decrementing;
public:
	CreatureCounter() : ladybugs(0), aphids(0), decrementing(false) {}
	void interact(Ladybug & ladybug) 
	{ 
		if(decrementing) ladybugs--; 
		else ladybugs++;
	}
	void interact(Aphid & aphid) 
	{ 
		if (decrementing) aphids--; 
		else aphids++;
	}
	void reset()
	{
		aphids = ladybugs = 0;
	}
	int getAphids() { return aphids; }
	int getLadybugs() { return ladybugs; }
	void setIncrementing() { decrementing = false; }
	void setDecrementing() { decrementing = true; }
};