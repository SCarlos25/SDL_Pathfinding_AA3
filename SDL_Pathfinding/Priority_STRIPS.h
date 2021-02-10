#pragma once
#include "STRIPS.h"

class Priority_STRIPS
{
public:
	STRIPS strips;
	float priority = 0;

	Priority_STRIPS(STRIPS gStrip, float gPriority);

public:
	bool friend operator<(const Priority_STRIPS& strips1, const Priority_STRIPS& strips2)
	{
		return strips1.priority > strips2.priority;
	}
	
	bool friend operator>(const Priority_STRIPS& strips1, const Priority_STRIPS& strips2)
	{
		return strips1.priority < strips2.priority;
	}
};