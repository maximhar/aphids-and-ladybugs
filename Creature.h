#pragma once

class Manager;
class Creature;
class Cell;
class CreatureCounter;

typedef void (Manager::*KilledCallback) (Creature & sender, Creature & victim);
typedef void (Manager::*MovedCallback) (Creature & sender, Cell * location);

class Creature 
{
private:
	KilledCallback killCallback;
	MovedCallback moveCallback;
public:
	virtual void count(CreatureCounter & counter) = 0;
};