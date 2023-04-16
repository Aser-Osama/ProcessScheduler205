#pragma once

#include "Processor.h"


class SJF :
    public Processor
{
    Queue<Process *> RDY;
public:
    void ScheduleAlgo() override; 
    friend ostream& operator<<(ostream& os, const SJF& prcsr);
    
    SJF();
    SJF(Queue<Process*> RDY) :RDY(RDY) {}
};

