#pragma once

#include "Processor.h"


class FCFS :
    public Processor
{
    LinkedList<Process*> RDY;
public:
    void SigKill(Process* P);
    void ScheduleAlgo() override; 
    void moveToRDY(Process* const &NewProcess) override;
    Process* getTopElem() override; 
    bool Execute(Process*&, int, int&) override;
    void attemptFork();
    Process* findProcess(int);
    Process* removeFromReady(int pid);
    friend ostream& operator<<(ostream& os, const FCFS& prcsr);
    bool readyIsEmpty() override;
    FCFS();
};

