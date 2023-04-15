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
	void set_RT(int);
	void set_TRT();
	void set_WT();
	friend ostream& operator<<(ostream& output, const Process& prcs);


	Process(int pid, int at, int ct, Map<int,int> io_r_d);
};

