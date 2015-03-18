#include "MatePicker.h"
#include "Creature.h"
#include "Aphid.h"
#include "Corpse.h"
#include "Ladybug.h"

Creature * MatePicker::pick(CreatureSorter & sorter, Aphid & subject)
{
	return sorter.getAphid();
}
Creature * MatePicker::pick(CreatureSorter & sorter, Ladybug & subject)
{
	return sorter.getLadybug();
}