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
	AphidConfiguration(char* path, char* extra);
protected:
	void setKillLadybugProbability(float p) { pKillLadybug = p; }
	void setKillLadybugGroupProbability(float p) { pKillLadybugGroup = p; }
	void printSpecificConfiguration()
	{
		std::cout << "APHID" << std::endl;
		std::cout << "Probability to kill a ladybug alone: " << getKillLadybugProbability() << std::endl;
		std::cout << "Probability to kill a ladybug in group: " << getKillLadybugGroupProbability() << std::endl;
	}
public:
	float getKillLadybugProbability() { return pKillLadybug; }
	float getKillLadybugGroupProbability() { return pKillLadybugGroup; }
	static AphidConfiguration &  get();
};