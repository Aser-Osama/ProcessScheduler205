#include "RR.h"


void RR::ScheduleAlgo(){

}

RR::RR(int RRnum){

}

ostream& operator<<(ostream& os, const RR& prcsr)
{
    os << "[RR]: " << prcsr.RDY.getCount() << "RDY: ";
    prcsr.RDY.Print();
    return os;
}