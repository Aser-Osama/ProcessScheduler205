#include "RR.h"


//void RR::ScheduleAlgo(){
////    cout<<"this is RR schedule algo";
////    Process* nR;
////    if (RDY.dequeue(nR)) {
////        cout<<*nR<<"this is a process";
////        setRUN(nR);
////        RDY.enqueue(nR);
////    }
////    else {
////        setRUN(nullptr);
////    }
////    
//
//}

void RR::ScheduleAlgo() {
    //Process* nR;
    //if (RDY.dequeue(nR)) //if a there is a process* to dequeue from RDY into nR
    //{
    //    if (nR->getRemainingTime() <0) {
    //        setRUN(nR); //sets the RUN to the dequeued process*
    //        RDY.enqueue(nR); //enqueues the process* again
    //        cout << "\n1\n";
    //    }
    //    else if (nR->getRemainingTime() == 0) {
    //        setRUN(nR); //sets the RUN to the dequeued process* without enqueuing
    //        cout << "\n2\n";
    //    }
    //}
    //else {
    //    setRUN(nullptr);
    //    cout << "\n3\n";
    //}
    Process* nR;
    cout << "inside sjf schedule algo";
    if (RDY.dequeue(nR)) { cout << "being set in schedule algo sjf"; setRUN(nR); }
    else {
        setRUN(nullptr); cout << "being set as null";
    }
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