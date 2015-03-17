#pragma once
#include <map>
#include <set>
#include <queue>
#include "CreatureCounter.h"
class Cell;
class WorldMap
{
public:
	struct CreatureCellPair
	{
		Cell * cell;
		Creature * creature;
		CreatureCellPair(Cell * ce, Creature * cr)
			: cell(ce), creature(cr)
		{}
	};
	class CreatureIterator
	{
	public:
		virtual bool hasNext() = 0;
		virtual CreatureCellPair next() = 0;
		virtual void reset() = 0;
		virtual CreatureIterator * copy() = 0;
	};
private:
	std::map<Cell *, std::set<Creature *> *> cellCreaturesMap;
	std::map<Cell *, CreatureCounter> cellCountersMap;
	std::map<Creature *, Cell *> creatureCellMap;
	std::queue<CreatureCellPair> additionQueue;
	std::queue<Creature *> deletionQueue;
	std::queue<CreatureCellPair> movementQueue;
	CreatureCounter totalsCounter;
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
		std::map<Creature *, Cell *>::const_iterator begin;
		std::map<Creature *, Cell *>::const_iterator end;
		std::map<Creature *, Cell *>::const_iterator current;
	public:
		CreatureMapIterator(std::map<Creature *, Cell *> * creatures)
			: begin(creatures->cbegin()), end(creatures->cend())
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
			: begin(creatures->cbegin()), end(creatures->cend()), cell(cell)
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
		cellCreaturesMap(std::map<Cell *, std::set<Creature *> *>()),
		creatureCellMap(std::map<Creature *, Cell *>())
	{
	}
	bool deleteCreature(Creature & creature);
	void addCreature(Creature & creature, Cell & cell)
	{
		additionQueue.push(CreatureCellPair(&cell, &creature));
	}
	void moveCreature(Creature & creature, Cell & newCell)
	{
		movementQueue.push(CreatureCellPair(&newCell, &creature));
	}
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
	const CreatureCounter getTotalsCounter()
	{
		return totalsCounter;
	}
	const CreatureCounter getCounterForCell(Cell & cell)
	{
		if (cellExists(cell)) return getCellCounter(cell);
		else return CreatureCounter();
	}
	~WorldMap();
	
};