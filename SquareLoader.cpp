#include "SquareLoader.h"
#include "SquareWorld.h"
#include "SquareCell.h"
#include "Aphid.h"
#include "Ladybug.h"
#include <istream>

void SquareLoader::place(std::map<Cell *, std::vector<Creature *>> * map, SquareWorld * world, Creature * creature, int col, int row)
{
	if (col > world->getWidth() || row > world->getHeight() || col < 0 || row < 0) throw "Coordinates out of world space.";

	Cell * c = &world->getOrigin();

	for (int x = 0; x < col; x++)
	{
		c = c->getNeighbour(SquareCell::RIGHT);
	}
	for (int y = 0; y < row; y++)
	{
		c = c->getNeighbour(SquareCell::BOTTOM);
	}

	map->insert(std::make_pair(c, std::vector<Creature *>())).first->second.push_back(creature);
}

bool SquareLoader::load(std::map<Cell *, std::vector<Creature *>> ** map, World ** world, std::istream & is)
{
	int width, height;
	is >> width >> height;
	*map = new std::map<Cell *, std::vector<Creature *>>();
	*world = new SquareWorld(width, height);
	SquareWorld * squareWorld = dynamic_cast<SquareWorld *>(*world);
	int aphidCount;
	is >> aphidCount;

	int x, y;
	for (int i = 0; i < aphidCount; i++)
	{
		is >> x >> y;
		Creature * aphid = new Aphid();
		place(*map, squareWorld, aphid, x, y);
	}

	int ladybugCount;
	is >> ladybugCount;

	for (int i = 0; i < ladybugCount; i++)
	{
		is >> x >> y;
		Creature * ladybug = new Ladybug();
		place(*map, squareWorld, ladybug, x, y);
	}

	return true;
}
