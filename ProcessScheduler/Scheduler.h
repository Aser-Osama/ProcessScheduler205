#pragma once

#include "Processors/FCFS.h"
#include "Processors/RR.h"
#include "Processors/SJF.h"
#include "UI.h"


class Scheduler
{
    private:
    int timestep;
    int total_nprocess;
    Map<int,int> parseIO_R_D(string);
    LinkedList<Processor*> Processors;
    Queue<Process*> NEW;
    Queue<Process*> BLK;
    Queue<Process*> TRM;
    Map<int, int> SIGKILL;
    int RTF, MaxW, STL, forkProb;

    public:

    void randomize_RUN(Processor* const &prcsr);
    void random_kill(Processor* const& prcsr);
    void randomize_BLK(Processor* const& prcsr);
    void load(string); //will be called 
    void save(string);
    void run(); //this is where the program is run
    Scheduler();
    ~Scheduler();

};

