#pragma once
class Creature;
class Aphid;
class Ladybug;
class CreatureCounter
{
private:
	int ladybugs, aphids;
public:
	void count(Ladybug & ladybug) { ladybugs++; }
	void count(Aphid & aphid) { aphids++; }
	void reset()
	{
		aphids = ladybugs = 0;
	}
	int getAphids() { return aphids; }
	int getLadybugs() { return ladybugs; }
};