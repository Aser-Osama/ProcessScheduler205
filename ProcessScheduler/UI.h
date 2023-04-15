#pragma once

#include <fstream>
#include <string>
#include "Processors/Processor.h"
#include "Process.h"
#include "ADT/Linked_Queue/Queue.h"

class UI
{
	void print_interactive(int c_ts, int n_processors, Processor* processors[], Queue<Process> BLK, Queue<Process> TRM); //waits for keypress 
	void print_sbs(int c_ts, int n_processors, Processor* processors[], Queue<Process> BLK, Queue<Process> TRM); //prints once a second
	void print_silent(); //does not print anything
	void general_template(int c_ts, int n_processors, Processor* processors[], Queue<Process> BLK, Queue<Process> TRM);
};

