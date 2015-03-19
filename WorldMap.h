#pragma once
#include <hash_map>
#include <hash_set>
#include <set>
#include <queue>
#include <iostream>
#include "CreatureCounter.h"
#include "CreatureSorter.h"
#include "CreatureIterator.h"
#include "CreatureCellPair.h"
#include "SorterManager.h"
#include "CreatureFamily.h"
class Cell;
class WorldMap
{
private:
	std::hash_map<Cell *, std::set<Creature *> *> cellCreaturesMap;
	std::hash_map<Cell *, CreatureCounter> cellCountersMap;
	std::hash_map<Creature *, Cell *> creatureCellMap;
	std::queue<CreatureFamily> additionQueue;
	std::queue<Creature *> deletionQueue;
	std::queue<CreatureCellPair> movementQueue;
	std::hash_set<Creature *> changePendingSet;
	SorterManager additionSorters;
	SorterManager deletionSorters;
	CreatureCounter totalsCounter;
	void addChangePending(Creature & creature)
	{
		changePendingSet.insert(&creature);
	}

	void removeChangePending(Creature & creature)
	{
		changePendingSet.erase(&creature);
	}

	bool cellExists(Cell & cell)
	{
		return cellCreaturesMap.count(&cell) > 0;
	}

	Cell * getCreatureCell(Creature & creature)
	{
		if (!creatureExists(creature)) return NULL;
		return creatureCellMap.find(&creature)->second;
	}

	CreatureCounter & getCellCounter(Cell & cell)
	{
		return cellCountersMap.find(&cell)->second;
	}

	void createCellIfNotExists(Cell & cell)
	{
		if (!cellExists(cell))
		{
			cellCreaturesMap.insert(std::make_pair(&cell, new std::set<Creature *>()));
			cellCountersMap.insert(std::make_pair(&cell, CreatureCounter()));
		}
	}

	void addCreatureToCell(Creature & creature, Cell & cell);
	void deleteCreatureFromCell(Creature & creature, Cell & cell);

	void addCreatureToSet(Creature & creature, Cell & cell)
	{
		creatureCellMap.insert(std::make_pair(&creature, &cell));
	}

	bool creatureExists(Creature & creature)
	{
		return creatureCellMap.count(&creature) > 0;
	}

	void deleteCreatureFromSet(Creature & creature)
	{
		creatureCellMap.erase(&creature);
	}

	void setCreatureCell(Creature & creature, Cell & cell)
	{
		creatureCellMap.find(&creature)->second = &cell;
	}

	void flushMovementQueue();

	void flushAdditionQueue();

	void flushDeletionQueue();

	class CreatureMapIterator : public CreatureIterator
	{
	private:
		std::hash_map<Creature *, Cell *>::const_iterator begin;
		std::hash_map<Creature *, Cell *>::const_iterator end;
		std::hash_map<Creature *, Cell *>::const_iterator current;
	public:
		CreatureMapIterator(std::hash_map<Creature *, Cell *> * creatures)
			: begin(creatures->begin()), end(creatures->end())
		{
			current = begin;
		}
		CreatureCellPair next()
		{
			if (current == end) return CreatureCellPair(NULL, NULL);
			auto pair = CreatureCellPair(current->second, current->first);
			++current;
			return pair;
		}
		bool hasNext()
		{
			return !(current == end);
		}
		void reset()
		{
			current = begin;
		}
		CreatureIterator * copy()
		{
			return new CreatureMapIterator(*this);
		}
	};
	class CreatureSetIterator : public CreatureIterator
	{
	private:
		std::set<Creature *>::const_iterator begin;
		std::set<Creature *>::const_iterator end;
		std::set<Creature *>::const_iterator current;
		Cell * cell;
	public:
		CreatureSetIterator(std::set<Creature *> * creatures, Cell * cell)
			: begin(creatures->begin()), end(creatures->end()), cell(cell)
		{
			current = begin;
		}
		CreatureCellPair next()
		{
			if (current == end) return CreatureCellPair(NULL, NULL);
			auto pair = CreatureCellPair(cell, *current);
			++current;
			return pair;
		}

		bool hasNext()
		{
			return !(current == end);
		}

		void reset()
		{
			current = begin;
		}
		CreatureIterator * copy()
		{
			return new CreatureSetIterator(*this);
		}
	};

public:
	WorldMap() :
		cellCreaturesMap(std::hash_map<Cell *, std::set<Creature *> *>()),
		creatureCellMap(std::hash_map<Creature *, Cell *>())
	{
	}
	bool deleteCreature(Creature & creature);
	void addCreature(Creature & creature, Creature & parent1, Creature & parent2, Cell & cell);
	void addCreature(Creature & creature, Cell & cell);
	void moveCreature(Creature & creature, Cell & newCell);
	void flush()
	{
		flushMovementQueue();
		flushDeletionQueue();
		flushAdditionQueue();
	}
	CreatureIterator * allCreatures()
	{
		return new CreatureMapIterator(&creatureCellMap);
	}
	CreatureIterator * creaturesInCell(Cell & cell)
	{
		if (!cellExists(cell)) return NULL;
		auto set = cellCreaturesMap.find(&cell);
		return new CreatureSetIterator(set->second, set->first);
	}
	CreatureCounter getTotalsCounter()
	{
		return totalsCounter;
	}
	CreatureCounter getCounterForCell(Cell & cell)
	{
		if (cellExists(cell)) return getCellCounter(cell);
		else return CreatureCounter();
	}
	CreatureSorter & getDeletionSorterForCell(Cell & cell)
	{
		if (cellExists(cell)) return deletionSorters.getSorter(cell);
		else throw "Nonexistent cell";
	}
	CreatureSorter & getAdditionSorterForCell(Cell & cell)
	{
		if (cellExists(cell)) return additionSorters.getSorter(cell);
		else throw "Nonexistent cell";
	}
	bool changePending(Creature & creature)
	{
		return changePendingSet.count(&creature) > 0;
	}
	~WorldMap();
	
};