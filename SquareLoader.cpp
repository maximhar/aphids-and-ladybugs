#include "SquareLoader.h"
#include "SquareWorld.h"
#include "SquareCell.h"
#include "Aphid.h"
#include "Ladybug.h"
#include "AphidConfiguration.h"
#include "LadybugConfiguration.h"
#include "CreatureConfiguration.h"
#include <istream>

void SquareLoader::place(WorldMap * map, SquareWorld * world, Creature * creature, int col, int row)
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
	map->addCreature(*creature, *c);
}

World * SquareLoader::load(WorldMap * map, std::istream & is)
{
	int width, height;
	is >> width >> height;
	SquareWorld * world = new SquareWorld(width, height);
	int aphidCount;
	is >> aphidCount;

	int x, y;
	for (int i = 0; i < aphidCount; i++)
	{
		is >> x >> y;
		Creature * aphid = new Aphid(AphidConfiguration::get().getLife(), AphidConfiguration::get().getStartingFood());
		place(map, world, aphid, x, y);
	}

	int ladybugCount;
	is >> ladybugCount;

	for (int i = 0; i < ladybugCount; i++)
	{
		is >> x >> y;
		Creature * ladybug = new Ladybug(LadybugConfiguration::get().getLife(), LadybugConfiguration::get().getStartingFood());
		place(map, world, ladybug, x, y);
	}

	return world;
}
