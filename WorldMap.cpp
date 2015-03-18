#include "WorldMap.h"
#include "Creature.h"
#include <iostream>
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
	auto setBegin = cellSortersMap.begin();
	auto setEnd = cellSortersMap.end();
	for (auto it = mapBegin; it != mapEnd; ++it)
	{
		delete it->second;
	}
}

bool WorldMap::deleteCreature(Creature & creature)
{
	if (!creatureExists(creature)) return false;
	deletionQueue.push(&creature);
	addChangePending(creature);
	return true;
}

void WorldMap::flushDeletionQueue()
{
	while (!deletionQueue.empty())
	{
		Creature * cr = deletionQueue.front();
		if (creatureExists(*cr))
		{
			totalsCounter.setDecrementing();
			cr->interactWith(totalsCounter);
			Cell * cell = getCreatureCell(*cr);
			deleteCreatureFromCell(*cr, *cell);
			deleteCreatureFromSet(*cr);
			removeChangePending(*cr);
			delete cr;
		}
		deletionQueue.pop();
	}
}

void WorldMap::flushMovementQueue()
{
	while (!movementQueue.empty())
	{
		CreatureCellPair pair = movementQueue.front();
		if (creatureExists(*pair.creature))
		{
			Cell & oldCell = *getCreatureCell(*pair.creature);
			setCreatureCell(*pair.creature, *pair.cell);
			deleteCreatureFromCell(*pair.creature, oldCell);
			addCreatureToCell(*pair.creature, *pair.cell);
			removeChangePending(*pair.creature);
		}
		movementQueue.pop();
	}
}

void WorldMap::flushAdditionQueue()
{
	while (!additionQueue.empty())
	{
		CreatureCellPair pair = additionQueue.front();
		totalsCounter.setIncrementing();
		pair.creature->interactWith(totalsCounter);
		addCreatureToCell(*pair.creature, *pair.cell);
		addCreatureToSet(*pair.creature, *pair.cell);
		additionQueue.pop();
	}
}

void WorldMap::addCreatureToCell(Creature & creature, Cell & cell)
{
	createCellIfNotExists(cell);
	auto set = cellCreaturesMap.find(&cell)->second;
	set->insert(&creature);
	CreatureCounter & counter = getCellCounter(cell);
	CreatureSorter & sorter = getCellSorter(cell);
	counter.setIncrementing();
	sorter.setAdding();
	creature.interactWith(counter);
	creature.interactWith(sorter);
}
void WorldMap::deleteCreatureFromCell(Creature & creature, Cell & cell)
{
	auto set = cellCreaturesMap.find(&cell)->second;
	set->erase(&creature);
	CreatureCounter & counter = getCellCounter(cell);
	CreatureSorter & sorter = getCellSorter(cell);
	counter.setDecrementing();
	sorter.setRemoving();
	creature.interactWith(counter);
	creature.interactWith(sorter);
}