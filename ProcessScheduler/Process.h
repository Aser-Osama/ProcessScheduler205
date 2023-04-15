#pragma once

#include "ADT/Map.h"


class Process
{
private:
	int PID, 
		AT,
		RT,
		CT,
		TT,
		TRT,
		FT, //THIS IS THE FIRST TIME ARRIVAL VARIABLE. SET THIS WHEN THE PROCESS FIRST ARRIVES AT A CPU 
		LT, // THIS IS THE LEFT OVER TIME. DECREMENT THIS USING THE METHOD TO REDUCE TIME REMAINING IN CPU RUN
		WT;

	Map<int,int> IO_R_D;

public:
	int get_PID();
	int get_AT();
	int get_RT();
	int get_CT();
	int get_TT();
	int get_TRT();
	int get_WT();
	Map<int,int> get_IO_R_D();

	void set_TT(int);

	void set_RT();
	void set_FT(int);
	bool sub_LT(); 
	void set_TRT();
	void set_WT();

	Process(int pid, int at, int ct, Map<int,int> io_r_d);
};

