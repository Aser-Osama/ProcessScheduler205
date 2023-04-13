#pragma once

#include "Processor.h"


class FCFS :
    public Processor
{
    Queue<Process> RDY;
public:
    void SigKill(Process* P);
    void ScheduleAlgo() override; 
    int getIdleTime() override;
    int getBusyTime() override;
};

