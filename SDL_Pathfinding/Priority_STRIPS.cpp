#include "Priority_STRIPS.h"

Priority_STRIPS::Priority_STRIPS(STRIPS gStrips, float gPriority)
{
	strips = gStrips;
	priority = gPriority;
}

/*bool operator<(const Priority_STRIPS& strips1, const Priority_STRIPS& strips2)
{
	return strips1.priority > strips2.priority;
}

bool operator>(const Priority_STRIPS& strips1, const Priority_STRIPS& strips2)
{
	return strips1.priority < strips2.priority;
}*/

