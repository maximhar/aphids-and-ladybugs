#pragma once
#include "CreatureConfiguration.h"
#define APHID_CONFIG "Aphid.txt"
#define APHID_EXTRA_CONFIG "Aphid_Extra.txt"
class AphidConfiguration : public CreatureConfiguration
{
private:
	static AphidConfiguration * config;
	float pKillLadybug;
	float pKillLadybugGroup;
	AphidConfiguration(char* path);
protected:
	void setKillLadybugProbability(float p) { pKillLadybug = p; }
	void setKillLadybugGroupProbability(float p) { pKillLadybugGroup = p; }
public:
	float getKillLadybugProbability() { return pKillLadybug; }
	float getKillLadybugGroupProbability() { return pKillLadybugGroup; }
	static AphidConfiguration &  get();
};