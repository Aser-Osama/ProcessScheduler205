#include "RR.h"


void RR::ScheduleAlgo(){

}

void RR::add_to_RDY(Process* const &prcs)
{
    RDY.enqueue(prcs);
}

RR::RR(int RRnum){

}

ostream& operator<<(ostream& os, const RR& prcsr)
{
    os << "[RR]: " << prcsr.RDY.getCount() << "RDY: ";
    prcsr.RDY.Print();
    return os;
}