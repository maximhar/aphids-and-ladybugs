#pragma once
#include <hash_map>
#include "CreatureSorter.h"
class Cell;

class SorterManager
{
private:
	std::hash_map<Cell *, CreatureSorter *> cellSorterMap;

	bool cellExists(Cell & cell)
	{
		return cellSorterMap.count(&cell) > 0;
	}

	void createCell(Cell & cell)
	{
		cellSorterMap.insert(std::make_pair(&cell, new CreatureSorter()));
	}

	CreatureSorter & getCellSorter(Cell & cell)
	{
		if (!cellExists(cell))
		{
			createCell(cell);
		}
		return *cellSorterMap.find(&cell)->second;
	}

public:

	CreatureSorter & getSorter(Cell & cell)
	{
		return getCellSorter(cell);
	}

	~SorterManager()
	{
		for (auto it = cellSorterMap.begin(); it != cellSorterMap.end(); it++)
		{
			delete it->second;
		}
	}
};