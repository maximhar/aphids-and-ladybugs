#pragma once

class CreatureConfiguration
{
private:
	float pMove;
	float pReproduce;
protected:
	void setMoveProbability(float p) { pMove = p; }
	void setReproduceProbability(float p) { pReproduce = p; }
public:
	float getMoveProbability() { return pMove; }
	float getReproduceProbability() { return pReproduce; }
};