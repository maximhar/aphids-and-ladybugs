#pragma once

class Manager;
class Creature;
class Cell;

typedef void (Manager::*KilledCallback) (Creature & sender, Creature & victim);
typedef void (Manager::*MovedCallback) (Creature & sender, Cell * location);

class Creature 
{
private:
	KilledCallback killCallback;
	MovedCallback moveCallback;
};