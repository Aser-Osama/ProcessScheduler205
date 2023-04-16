#include "SJF.h"


void SJF::ScheduleAlgo(){

}

SJF::SJF(){
	
}

ostream& operator<<(ostream& os, const SJF& prcsr)
{
    os << "[FCFS]: " << prcsr.RDY.getCount() << "RDY: ";
    prcsr.RDY.Print();
    return os;
}
