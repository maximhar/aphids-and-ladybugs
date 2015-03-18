#pragma once
#include <unordered_set>
#include "CreatureInteractor.h"
class Creature;
class Aphid;
class Ladybug;
class Corpse;
class CreatureSorter : public CreatureInteractor
{
private:
	std::unordered_set<Aphid *> aphids;
	std::unordered_set<Ladybug *> ladybugs;
	std::unordered_set<Corpse *> corpses;
	std::unordered_set<Aphid *>::iterator itAphids;
	std::unordered_set<Ladybug *>::iterator itLadybugs;
	std::unordered_set<Corpse *>::iterator itCorpses;
	bool adding;
public:
	CreatureSorter() : adding(true)
	{
		begin();
	}
	void interact(Ladybug & ladybug)
	{
		if (adding) ladybugs.insert(&ladybug);
		else ladybugs.erase(&ladybug);
		itLadybugs = ladybugs.begin();
	}
	void interact(Aphid & aphid)
	{
		if (adding) aphids.insert(&aphid);
		else aphids.erase(&aphid);
		itAphids = aphids.begin();
	}
	void interact(Corpse & corpse)
	{
		if (adding) corpses.insert(&corpse);
		else corpses.erase(&corpse);
		itCorpses = corpses.begin();
	}
	Aphid * getAphid()
	{
		if (aphids.empty()) return NULL;
		if (itAphids == aphids.end())
		{
			itAphids = aphids.begin();
			return NULL;
		}
		return *(itAphids++);
	}
	Corpse * getCorpse() 
	{ 
		if (corpses.empty()) return NULL;
		if (itCorpses == corpses.end())
		{
			itCorpses = corpses.begin();
			return NULL;
		}
		return *(itCorpses++);
	}
	Ladybug * getLadybug() 
	{ 
		if (ladybugs.empty()) return NULL;
		if (itLadybugs == ladybugs.end())
		{
			itLadybugs = ladybugs.begin();
			return NULL;
		}
		return *(itLadybugs++);
	}
	void begin()
	{
		itLadybugs = ladybugs.begin();
		itAphids = aphids.begin();
		itCorpses = corpses.begin();
	}
	void setAdding() { adding = true; }
	void setRemoving() { adding = false; }
};