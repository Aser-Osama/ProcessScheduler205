#pragma once

#include "Processor.h"


class SJF :
    public Processor
{
    Queue<Process *> RDY; //should be modified to priority queue asap
public:
    void ScheduleAlgo() override; 
    friend ostream& operator<<(ostream& os, const SJF& prcsr);
    void add_to_RDY(Process* const &prcs) override;

    SJF();
};

