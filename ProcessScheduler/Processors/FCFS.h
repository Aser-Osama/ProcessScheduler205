#pragma once

#include "Processor.h"


class FCFS :
    public Processor
{
    Queue<Process *> RDY;
public:
    void SigKill(Process* P);
    void ScheduleAlgo() override; 
    void MoveToRDY(Process* NewProcess) override;
    friend ostream& operator<<(ostream& os, const FCFS& prcsr);

    FCFS();
    FCFS(Queue<Process*> rdy) : RDY(rdy){} //HERE FOR TESTING ONLY
};

