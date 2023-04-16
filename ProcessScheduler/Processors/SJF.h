#pragma once

#include "Processor.h"


class SJF :
    public Processor
{
    Queue<Process *> RDY;
public:
    void ScheduleAlgo() override; 
    void MoveToRDY(Process* NewProcess) override;
    friend ostream& operator<<(ostream& os, const SJF& prcsr);
    
    SJF();
};

