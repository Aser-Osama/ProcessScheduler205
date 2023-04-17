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
    UI MAINUI;
    int RTF, MaxW, STL, forkProb;

    public:
    void Initialize_RDY();
    void simulator();
    void randomizeRUN(Processor* const &prcsr);
    void randomKill(Processor* const& prcsr);
    void randomizeBLK(Processor* const& prcsr);
    void load(string); //will be called 
    void save(string);
    void run(); //this is where the program is run
    Scheduler(string);
    ~Scheduler();

};

