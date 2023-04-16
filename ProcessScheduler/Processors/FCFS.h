#pragma once

#include "Processor.h"


class FCFS :
    public Processor
{
    LinkedList<Process *> RDY;
public:
    void SigKill(Process* P);
    void ScheduleAlgo() override; 
    
    FCFS();
    friend ostream& operator<<(ostream& os, const FCFS& prcsr);
};

