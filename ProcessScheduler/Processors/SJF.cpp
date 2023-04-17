#include "SJF.h"


void SJF::ScheduleAlgo(){
    /*Process* nR;
    RDY.dequeue(nR);
    setRUN(nR);
    RDY.enqueue(nR);
    untill PQ implemenation is done*/

}


SJF::SJF(){
	
}


void SJF::moveToRDY(Process* NewProcess)
{
    RDY.enqueue(NewProcess);
}

ostream& operator<<(ostream& os, const SJF& prcsr)
{
    //os << "[SJF]: " << prcsr.RDY.getCount() << "RDY: ";
    //prcsr.RDY.Print();
    return os;
}
