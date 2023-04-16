#pragma once

#include "ADT/Map.h"
#include <iostream>
#include <ostream>
using namespace std;
class Process
{
private:
	int PID, 
		childPID,
		AT,
		RT,
		CT,
		TT,
		TRT,
		cpuArrivalTime, //THIS IS THE FIRST TIME ARRIVAL to cpu VARIABLE. SET THIS WHEN THE PROCESS FIRST ARRIVES AT A CPU 
		remainingTime, // THIS IS THE LEFT OVER TIME. DECREMENT THIS USING THE METHOD TO REDUCE TIME REMAINING IN CPU RUN
		WT;
	Map<int,int> IO_R_D;

public:
	int getPID() const;
	int getChildPID() const;
	int getAT() const;
	int getRT() const;
	int getCT() const;
	int getTT() const;
	int getTRT()const;
	int getWT()const;
	Map<int,int> getIO_R_D ()const;


	void setTT(int);

	void setRT();
	void setCpuArrivalTime(int);
	bool subRemainingTime(); 
	void setTRT();
	void setWT();

	friend ostream& operator<<(ostream& os, const Process& prcs);
	bool operator==(const Process &);

	Process(int pid, int at, int ct, Map<int,int> io_r_d);
	Process();
};

