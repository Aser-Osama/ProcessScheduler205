#pragma once

#include "Processor.h"


class RR :
    public Processor
{
    Queue<Process *> RDY;
public:
    void ScheduleAlgo() override; 
    RR(int);
};

