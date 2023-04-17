#pragma once

#include <windows.h>
#include <string>
#include <fstream>
#include "Processors/Processor.h"
#include "Process.h"
#include "ADT/Linked_Queue/Queue.h"
#include "ADT/LinkedList.h"
#include "ADT/Node.h"
#include "Processors/FCFS.h"
#include "Processors/RR.h"
#include "Processors/SJF.h"
class UI
{
public:
	void print_interactive(int c_ts, LinkedList<Processor*> processors, Queue<Process*> BLK, Queue<Process*> TRM); //waits for keypress 
	void print_sbs(int c_ts, LinkedList<Processor*> processors, Queue<Process*> BLK, Queue<Process*> TRM); //prints once a second
	void print_silent(); //does not print anything
	void general_template(int c_ts, LinkedList<Processor*> processors, Queue<Process*> BLK, Queue<Process*> TRM);
};

