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
    int total_nprocess_forked=0;
    int total_notarrived;
    int nprocessor;
	int NF, NS, NR, RRSlice;
    Map<int,int> parseIO_R_D(string);
    LinkedList<Processor*> Processors;
    Queue<Process*> NEW;
    Queue<Process*> BLK;
    Queue<Process*> TRM;
    Node<Processor*>* StartingPoint;
    Map<int, int> SIGKILL_MAP;
    UI MAIN_UI;
    int RTF, MaxW, STL, forkProb;
    int ncpu;
    Process* RUN_BLK;

    public:
    void Initialize_RDY();
    void simulator();
    //void Fill_Rdy();
    Node<Processor*>* ProcessorWithShortestQueue();
    void NEWToRDY();
    void RUNToTRM(Process* P);
    void BLKToRDY();
    void load(string); //will be called 
    void save(string);
    void run(); //this is where the program is run
    void stealTask();
    bool migratedMaxW(Process* const &prcs);
    bool migratedRTF(Process*const &prcs);
    int getForkProb();
    void killSignal();
    Process* ForkProcess(int child_ct);
    void killOrphans(Process*);
    void ProcessorOverheat(int timesteps);
    Scheduler(string);
    ~Scheduler();


};

