#pragma once

#include "Processor.h"


class RR :
    public Processor
{
    int RR_SLICE;
    int current_rr_ts = 0;
    Queue<Process *> RDY;
public:
    void ScheduleAlgo() override; 
    void moveToRDY(Process* const& NewProcess)  override;
    bool Execute(Process*& P, int crnt_ts, int& io_length) override;
    friend ostream& operator<<(ostream& os, const RR& prcsr);

    RR(int);
};

