#pragma once

#include "ADT/Map.h"

class Process
{
public:
	int PID, 
		AT,
		RT,
		CT,
		TT,
		TRT,
		WT;

	Map IO_R_D;
};

