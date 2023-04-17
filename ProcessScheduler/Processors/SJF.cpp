#include "SJF.h"


void SJF::ScheduleAlgo(){
    Process* nR;
    if (RDY.dequeue(nR)) setRUN(nR);
    else {
        setRUN(NULL);
    }
}


SJF::SJF(){
	
}


void SJF::moveToRDY(Process* const& NewProcess)
{
    RDY.enqueue(NewProcess);
}

ostream& operator<<(ostream& os, const SJF& prcsr)
{
    //os << "[SJF]: " << prcsr.RDY.getCount() << "RDY: ";
    //prcsr.RDY.Print();
    return os;
}
