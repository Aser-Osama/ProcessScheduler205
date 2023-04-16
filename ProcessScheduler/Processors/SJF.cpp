#include "SJF.h"


void SJF::ScheduleAlgo(){

}

SJF::SJF(){
	
}

}

void SJF::MoveToRDY(Process* NewProcess)
{
    RDY.enqueue(NewProcess);
}

ostream& operator<<(ostream& os, const SJF& prcsr)
{
    os << "[SJF]: " << prcsr.RDY.getCount() << "RDY: ";
    prcsr.RDY.Print();
    return os;
}
