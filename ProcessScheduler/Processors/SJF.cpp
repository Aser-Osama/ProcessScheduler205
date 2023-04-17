#include "SJF.h"


void SJF::ScheduleAlgo(){

}

void SJF::add_to_RDY(Process* const &prcs)
{
    RDY.enqueue(prcs);
}

SJF::SJF(){
	
}

ostream& operator<<(ostream& os, const SJF& prcsr)
{
    os << "[SJF]: " << prcsr.RDY.getCount() << "RDY: ";
    prcsr.RDY.Print();
    return os;
}
