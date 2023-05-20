#include "SJF.h"


void SJF::ScheduleAlgo(){
    Process* nR;
    if (RDY.dequeue(nR)) {
        setRUN(nR);
    }
    else {
        setRUN(nullptr);
    }
}


SJF::SJF(){
	
}


void SJF::moveToRDY(Process* const& NewProcess)
{
    this->currentBusyTime += NewProcess->getCT();
    RDY.enqueue(NewProcess);
}

ostream& operator<<(ostream& os, const SJF& prcsr)
{
    os << "[SJF]: " << prcsr.RDY.getCount() << " RDY: ";
    prcsr.RDY.Print();
    return os;
}

Process* SJF::getTopElem()
{
	Process* top;
    if (!RDY.dequeue(top)) { return nullptr; }
    this->currentBusyTime -= top->getCT();
	return top;
}