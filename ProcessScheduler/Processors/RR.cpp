#include "RR.h"


void RR::ScheduleAlgo(){
    Process* nR;
    RDY.dequeue(nR);
    setRUN(nR);
    RDY.enqueue(nR);
}

void RR::add_to_RDY(Process* const &prcs)
{
    RDY.enqueue(prcs);
}

RR::RR(int RRnum){
}

void RR::MoveToRDY(Process* NewProcess)
{
    RDY.enqueue(NewProcess);
}

ostream& operator<<(ostream& os, const RR& prcsr)
{
    os << "[RR]: " << prcsr.RDY.getCount() << "RDY: ";
    prcsr.RDY.Print();
    return os;
}