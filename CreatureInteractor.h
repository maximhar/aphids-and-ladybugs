#pragma once
class Aphid;
class Ladybug;
class Corpse;
class CreatureInteractor
{
public:
	virtual void interact(Aphid & creature) = 0;
	virtual void interact(Ladybug & creature) = 0;
	virtual void interact(Corpse & creature) = 0;
};