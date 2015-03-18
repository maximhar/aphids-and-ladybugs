#include "FoePicker.h"
#include "Creature.h"
#include "Aphid.h"
#include "Corpse.h"
#include "Ladybug.h"

Creature * FoePicker::pick(CreatureSorter & sorter, Aphid & subject)
{
	Creature * cr = sorter.getLadybug();
	if (cr == NULL) cr = sorter.getCorpse();
	return cr;
}
Creature * FoePicker::pick(CreatureSorter & sorter, Ladybug & subject)
{
	Creature * cr = sorter.getAphid();
	if (cr == NULL) cr = sorter.getCorpse();
	return cr;
}