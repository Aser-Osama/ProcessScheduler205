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
    Node<Processor*>* StartingPoint;
    Map<int, int> SIGKILL;
    UI MAIN_UI;
    int RTF, MaxW, STL, forkProb;
    int ncpu;

    public:
    void Initialize_RDY();
    void simulator();
    void Fill_Rdy();
    void randomizeRUN(Processor* const &prcsr);
    void randomKill(Processor* const& prcsr);
    void randomizeBLK(Processor* const& prcsr);
    void load(string); //will be called 
    void save(string);
    void run(); //this is where the program is run
    void stealTask();
    bool migratedMaxW(Process* const &prcs);
    bool migratedRTF(Process*const &prcs);
    Scheduler(string);
    ~Scheduler();

};

