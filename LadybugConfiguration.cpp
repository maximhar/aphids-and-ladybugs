#include "LadybugConfiguration.h"
#include <fstream>
#include <cstddef>

LadybugConfiguration * LadybugConfiguration::config = NULL;

LadybugConfiguration & LadybugConfiguration::get()
{
	if (config == NULL)
	{
		config = new LadybugConfiguration(LADYBUG_CONFIG);
	}
	return *config;
}

LadybugConfiguration::LadybugConfiguration(char * path)
{
	 std::ifstream is(path);
	 float move, change, kill, reproduce, life, nutVal, startFood, foodPerTurn;
	 is >> move >> change >> kill >> reproduce >> life >> nutVal >> startFood >> foodPerTurn;
	 is.close();

	 setMoveProbability(move);
	 setDirectionChangeProbability(change);
	 setKillAphidProbability(kill);
	 setReproduceProbability(reproduce);
	 setLife(life);
	 setNutritionalValue(nutVal);
	 setStartingFood(startFood);
	 setFoodPerTurn(foodPerTurn);
}