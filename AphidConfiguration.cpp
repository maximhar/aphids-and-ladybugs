#include "AphidConfiguration.h"
#include <fstream>
#include <cstddef>

AphidConfiguration * AphidConfiguration::config = NULL;

AphidConfiguration & AphidConfiguration::get()
{
	if (config == NULL)
	{
		config = new AphidConfiguration(APHID_CONFIG);
	}
	return *config;
}

AphidConfiguration::AphidConfiguration(char * path)
{
	std::ifstream is(path);
	float move, kill, killGroup, reproduce;
	is >> move >> kill >> killGroup >> reproduce;
	is.close();

	setMoveProbability(move);
	setKillLadybugProbability(kill);
	setKillLadybugGroupProbability(killGroup);
	setReproduceProbability(reproduce);
}