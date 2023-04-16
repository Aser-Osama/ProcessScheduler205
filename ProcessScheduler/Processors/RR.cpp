#include "RR.h"


void RR::ScheduleAlgo(){

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