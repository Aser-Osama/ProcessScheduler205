#pragma once

#include "ADT/Map.h"
#include <iostream>
#include <ostream>
using namespace std;
class Process
{
private:
	int PID, 
		AT,
		RT,
		CT,
		TT,
		TRT,
		cpu_arrival_time, //THIS IS THE FIRST TIME ARRIVAL to cpu VARIABLE. SET THIS WHEN THE PROCESS FIRST ARRIVES AT A CPU 
		remaining_time, // THIS IS THE LEFT OVER TIME. DECREMENT THIS USING THE METHOD TO REDUCE TIME REMAINING IN CPU RUN
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
	void set_cpu_arrival_time(int);
	bool sub_remaining_time(); 
	void set_TRT();
	void set_WT();
	friend ostream& operator<<(ostream& output, const Process& prcs);


	Process(int pid, int at, int ct, Map<int,int> io_r_d);
};

