#pragma once

#include "Processor.h"


class FCFS :
    public Processor
{
    LinkedList<Process *> RDY;
public:
    void SigKill(Process* P);
    void ScheduleAlgo() override; 
    void add_to_RDY(Process* const &prcs) override;
    void remove_from_rdy(int pid);
    friend ostream& operator<<(ostream& os, const FCFS& prcsr);
    
    FCFS();
};

