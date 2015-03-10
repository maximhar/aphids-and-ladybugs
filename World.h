#pragma once

#include <vector>
#include <ostream>
#include "Cell.h"
#include "Printer.h"

class World
{
private:
	Printer * printer;
	Cell ** const cells;
	const int cellCount;
protected:
	//a way to allow derived classes to access the cell's internals
	void setCellNeighbour(Cell * cell, Cell * neighbour, int index)
	{
		cell->setNeighbour(index, neighbour);
	}

	World(int count, Printer * printer) : cellCount(count), cells(new Cell *[count]), printer(printer) { }
	
	int getCellCount() { return cellCount; }

	Cell& cellAt(int index) { return *cells[index]; }

	void cellSet(int index, Cell * cell) { cells[index] = cell; }
public:
	virtual Cell & getOrigin() = 0;
	virtual Printer & getPrinter()
	{
		return *printer;
	}
	virtual ~World()
	{
		for (int i = 0; i < cellCount; i++)
		{
			delete cells[i];
		}
		delete cells;
		delete printer;
	}
};