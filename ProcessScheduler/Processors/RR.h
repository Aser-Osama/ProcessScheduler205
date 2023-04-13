#pragma once

#include "Processor.h"


class RR :
    public Processor
{
    Queue<Process> RDY;
public:
    void ScheduleAlgo() override; 
    int getIdleTime() override;
    int getBusyTime() override;
    RR(int);
};

