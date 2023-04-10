#pragma once

#include "ADT/Map.h"

enum State
{
	NEW,
	RDY,
	RUN,
	BLK,
	TRM,
	ORPH
};


class Process
{
private:
	int PID, 
		AT,
		RT,
		CT,
		TT,
		TRT,
		WT;

	Map IO_R_D;
	State PS; // this is the process state variable. Process states are stored here

public:
	int get_PID();
	int get_AT();
	int get_RT();
	int get_CT();
	int get_TT();
	int get_TRT();
	int get_WT();
	Map get_IO_R_D();
	State get_State();

	void set_TT(int);
	void set_RT(int);
	void set_TRT();
	void set_WT();
	void set_State(State);

	Process(int pid, int at, int ct, Map io_r_d);
};

