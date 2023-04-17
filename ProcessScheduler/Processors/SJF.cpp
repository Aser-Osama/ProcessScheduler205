#include "SJF.h"


void SJF::ScheduleAlgo(){
    Process* nR;
    cout<<"inside sjf schedule algo";
    if (RDY.dequeue(nR)) {cout<<"being set in schedule algo sjf";setRUN(nR);}
    else {
        setRUN(nullptr);cout<<"being set as null";
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
    os << "[SJF]: " << prcsr.RDY.getCount() << " RDY: ";
    prcsr.RDY.Print();
    return os;
}
