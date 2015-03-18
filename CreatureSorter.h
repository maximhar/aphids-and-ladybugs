#pragma once
#include <set>
#include "CreatureInteractor.h"
class Creature;
class Aphid;
class Ladybug;
class Corpse;
class CreatureSorter : public CreatureInteractor
{
private:
	std::set<Aphid *> * aphids;
	std::set<Ladybug *> * ladybugs;
	std::set<Corpse *> * corpses;
	std::set<Aphid *>::iterator itAphids;
	std::set<Ladybug *>::iterator itLadybugs;
	std::set<Corpse *>::iterator itCorpses;
	bool adding;
public:
	CreatureSorter() : adding(true)
	{
		aphids = new std::set<Aphid *>();
		itAphids = aphids->begin();
		ladybugs = new std::set<Ladybug *>();
		itLadybugs = ladybugs->begin();
		corpses = new std::set<Corpse *>();
		itCorpses = corpses->begin();
	}
	void interact(Ladybug & ladybug)
	{
		if (adding) ladybugs->insert(&ladybug);
		else ladybugs->erase(&ladybug);
		itLadybugs = ladybugs->begin();
	}
	void interact(Aphid & aphid)
	{
		if (adding) aphids->insert(&aphid);
		else aphids->erase(&aphid);
		itAphids = aphids->begin();
	}
	void interact(Corpse & corpse)
	{
		if (adding) corpses->insert(&corpse);
		else corpses->erase(&corpse);
		itCorpses = corpses->begin();
	}
	Aphid * getAphid()
	{
		if (aphids->empty()) return NULL;
		if (itAphids == aphids->end()) itAphids = aphids->begin();
		return *itAphids;
	}
	Corpse * getCorpse() 
	{ 
		if (corpses->empty()) return NULL;
		if (itCorpses == corpses->end()) itCorpses = corpses->begin();
		return *itCorpses;
	}
	Ladybug * getLadybug() 
	{ 
		if (ladybugs->empty()) return NULL;
		if (itLadybugs == ladybugs->end()) itLadybugs = ladybugs->begin();
		return *itLadybugs;
	}
	void setAdding() { adding = true; }
	void setRemoving() { adding = false; }
	~CreatureSorter()
	{
		delete aphids;
		delete ladybugs;
		delete corpses;
	}
};