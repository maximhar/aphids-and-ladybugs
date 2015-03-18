#include "LadybugConfiguration.h"
#include <fstream>
#include <cstddef>

LadybugConfiguration * LadybugConfiguration::config = NULL;

LadybugConfiguration & LadybugConfiguration::get()
{
	if (config == NULL)
	{
		config = new LadybugConfiguration(LADYBUG_CONFIG, LADYBUG_EXTRA_CONFIG);
	}
	return *config;
}

LadybugConfiguration::LadybugConfiguration(char * path, char * extra)
{
	readExtraConfiguration(extra);
	std::ifstream is(path);
	float move = 0.7, change = 0.2, kill = 0.4, reproduce = 0.2;
	is >> move >> change >> kill >> reproduce;
	is.close();

	setMoveProbability(move);
	setDirectionChangeProbability(change);
	setKillAphidProbability(kill);
	setReproduceProbability(reproduce);
}