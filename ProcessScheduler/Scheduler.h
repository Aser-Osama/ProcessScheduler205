#pragma once

#include "Processors/FCFS.h"
#include "Processors/RR.h"
#include "Processors/SJF.h"
#include "UI.h"


class Scheduler
{
    private:
    int timestep;
    Map<int,int> parseIO_R_D(string);
    LinkedList<Processor*> Processors;
    Queue<Process*> NEW;
//  PlaceholderList<Process*> BLK;
//  PlaceholderList<Process*> TRM;
    Map<int, int> SIGKILL;
    int RTF, MaxW, STL, forkProb;

    public:
    void load(string); //will be called 
    void save(string);
    void run(); //this is where the program is run
    Scheduler();

};

