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
}

bool WorldMap::deleteCreature(Creature & creature)
{
	if (!creatureExists(creature)) return false;
	deletionQueue.push(&creature);
	addChangePending(creature);
	CreatureSorter& sorter = deletionSorters.getSorter(*getCreatureCell(creature));
	sorter.setRemoving();
	creature.interactWith(sorter);
	return true;
}


void WorldMap::addCreature(Creature & creature, Creature & parent1, Creature & parent2, Cell & cell)
{
	additionQueue.push(CreatureFamily(&cell, &creature, &parent1, &parent2));
	CreatureSorter & addsorter = additionSorters.getSorter(cell);
	addsorter.setRemoving();
	parent1.interactWith(addsorter);
	parent2.interactWith(addsorter);
}
void WorldMap::addCreature(Creature & creature, Cell & cell)
{
	additionQueue.push(CreatureFamily(&cell, &creature, &creature, &creature));
}
void WorldMap::moveCreature(Creature & creature, Cell & newCell)
{
	movementQueue.push(CreatureCellPair(&newCell, &creature));
	addChangePending(creature);
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
		CreatureFamily pair = additionQueue.front();
		totalsCounter.setIncrementing();
		pair.child->interactWith(totalsCounter);
		addCreatureToCell(*pair.child, *pair.location);
		addCreatureToSet(*pair.child, *pair.location);
		CreatureSorter & addsorter = additionSorters.getSorter(*pair.location);
		addsorter.setAdding();
		if (creatureExists(*pair.parent1))
			pair.parent1->interactWith(addsorter);
		if (creatureExists(*pair.parent2))
			pair.parent2->interactWith(addsorter);
		additionQueue.pop();
	}
}

void WorldMap::addCreatureToCell(Creature & creature, Cell & cell)
{
	createCellIfNotExists(cell);
	auto set = cellCreaturesMap.find(&cell)->second;
	set->insert(&creature);
	CreatureCounter & counter = getCellCounter(cell);
	CreatureSorter & delsorter = deletionSorters.getSorter(cell);
	CreatureSorter & addsorter = additionSorters.getSorter(cell);
	counter.setIncrementing();
	delsorter.setAdding();
	addsorter.setAdding();
	creature.interactWith(counter);
	creature.interactWith(delsorter);
	creature.interactWith(addsorter);
}
void WorldMap::deleteCreatureFromCell(Creature & creature, Cell & cell)
{
	auto set = cellCreaturesMap.find(&cell)->second;
	set->erase(&creature);
	CreatureCounter & counter = getCellCounter(cell);
	CreatureSorter & delsorter = deletionSorters.getSorter(cell);
	CreatureSorter & addsorter = additionSorters.getSorter(cell);
	counter.setDecrementing();
	delsorter.setRemoving();
	addsorter.setRemoving();
	creature.interactWith(counter);
	creature.interactWith(delsorter);
	creature.interactWith(addsorter);
}
