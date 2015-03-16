#include "WorldMap.h"
#include "Creature.h"
WorldMap::~WorldMap() 
{
	auto mapBegin = cellCreaturesMap.begin();
	auto mapEnd = cellCreaturesMap.begin();
	for (auto it = mapBegin; it != mapEnd; ++it)
	{
		auto setBegin = it->second->begin();
		auto setEnd = it->second->end();
		for (auto it2 = setBegin; it2 != setEnd; ++it2)
		{
			delete *it2;
		}
		delete it->second;
	}
}

bool WorldMap::deleteCreature(Creature & creature)
{
	if (!creatureExists(creature)) return false;
	deletionQueue.push(&creature);
	return true;
}

void WorldMap::flushDeletionQueue()
{
	while (!deletionQueue.empty())
	{
		Creature * cr = deletionQueue.front();
		if (creatureExists(*cr))
		{
			Cell * cell = getCreatureCell(*cr);
			deleteCreatureFromCell(*cr, *cell);
			deleteCreatureFromSet(*cr);
			delete cr;
		}
		deletionQueue.pop();
	}
}