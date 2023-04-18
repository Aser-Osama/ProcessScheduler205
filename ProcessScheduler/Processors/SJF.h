#pragma once

#include "Processor.h"


class SJF :
    public Processor
{
    PriorityQueue<Process *> RDY;
public:
    void ScheduleAlgo() override; 
    void moveToRDY(Process* const& NewProcess)  override;
    friend ostream& operator<<(ostream& os, const SJF& prcsr);
    SJF();
};

