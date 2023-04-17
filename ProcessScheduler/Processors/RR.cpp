#include "RR.h"


void RR::ScheduleAlgo(){
//    cout<<"this is RR schedule algo";
//    Process* nR;
//    if (RDY.dequeue(nR)) {
//        cout<<*nR<<"this is a process";
//        setRUN(nR);
//        RDY.enqueue(nR);
//    }
//    else {
//        setRUN(nullptr);
//    }
//    
}


RR::RR(int RRnum){
}

void RR::moveToRDY(Process* const& NewProcess)
{
    RDY.enqueue(NewProcess);
}

ostream& operator<<(ostream& os, const RR& prcsr)
{
    os << "[RR]: " << prcsr.RDY.getCount() << " RDY: ";
    prcsr.RDY.Print();
    return os;
}