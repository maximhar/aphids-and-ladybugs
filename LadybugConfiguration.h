#pragma once
#include "CreatureConfiguration.h"
#define LADYBUG_CONFIG "Ladybug.txt"
#define LADYBUG_EXTRA_CONFIG "Ladybug_Extra.txt"
class LadybugConfiguration : public CreatureConfiguration
{
private:
	static LadybugConfiguration * config;
	float pDirection;
	float pKillAphid;
	LadybugConfiguration(char* path);
protected:
	void setDirectionChangeProbability(float p) { pDirection = p; }
	void setKillAphidProbability(float p) { pKillAphid = p; }
public:
	float getDirectionChangeProbability() { return pDirection; }
	float getKillAphidProbability() { return pKillAphid; }
	static LadybugConfiguration &  get();
};