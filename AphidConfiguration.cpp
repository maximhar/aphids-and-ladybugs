#include "AphidConfiguration.h"
#include <fstream>
#include <cstddef>

AphidConfiguration * AphidConfiguration::config = NULL;

AphidConfiguration & AphidConfiguration::get()
{
	if (config == NULL)
	{
		config = new AphidConfiguration(APHID_CONFIG, APHID_EXTRA_CONFIG);
	}
	return *config;
}

AphidConfiguration::AphidConfiguration(char * path, char * extra)
{
	readExtraConfiguration(extra);
	std::ifstream is(path);
	float move = 0.7f, kill = 0.2f, killGroup = 0.1f, reproduce = 0.8f;
	if (is.is_open())
	{
		is >> move >> kill >> killGroup >> reproduce;
		is.close();
	}

	setMoveProbability(move);
	setKillLadybugProbability(kill);
	setKillLadybugGroupProbability(killGroup);
	setReproduceProbability(reproduce);
}