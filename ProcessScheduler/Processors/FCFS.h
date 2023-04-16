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
    FCFS(LinkedList<Process*> rdy) : RDY(rdy){} //HERE FOR TESTING ONLY
    friend ostream& operator<<(ostream& os, const FCFS& prcsr);
};

