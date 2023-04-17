#pragma once

#include "Processor.h"


class FCFS :
    public Processor
{
    LinkedList<Process *> RDY;
public:
    void SigKill(Process* P);
    void ScheduleAlgo() override; 
    void moveToRDY(Process* NewProcess) override;
    friend ostream& operator<<(ostream& os, const FCFS& prcsr);

    void removeFromReady(int pid);
    friend ostream& operator<<(ostream& os, const FCFS& prcsr);
    
    FCFS();
};

