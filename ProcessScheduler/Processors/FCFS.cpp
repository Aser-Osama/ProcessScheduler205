#include "FCFS.h"

void FCFS::SigKill(Process* P){
    //search for the the process in  the RUN or RDY list then move it TRM 
    //then calculate the statistics of the process like CT, etc.
    TotalTime -= P->getCT();
}

void FCFS::ScheduleAlgo(){
    Node<Process*>* nR;
    nR = RDY.getHead();
    if (nR) {
        setRUN(nR->getItem());
        TotalTime -= RDY.getHead()->getItem()->getCT();
        RDY.DeleteFirst();
    }
    else {
        setRUN(nullptr);
    }
}


  

Process* FCFS::removeFromReady(int pid)
{
    Node<Process*>* head = RDY.getHead();
    Process* to_remove;
    if (!head) return nullptr;

    while (head->getNext())
    {
        if (head->getItem()->find_by_pid(pid))
        {
            to_remove = head->getItem();
            RDY.DeleteNode(to_remove);
            return to_remove; //assuming 2 processes cant have the same pid
        }
        else 
        {
            head = head->getNext();
        }
    }
    return nullptr;
    
}

FCFS::FCFS(){

}

//int FCFS::GetMinCT()
//{
//    int totalCT = 0;
//    Node<Process*> *process = RDY.getHead();
//    if (!RDY.getHead()) return 0;
//    while (process->getNext())
//    {
//        totalCT += process->getItem()->getCT();
//        process = process->getNext();
//    }
//    totalCT += process->getItem()->getCT();
//}

void FCFS::moveToRDY(Process* const& NewProcess)
{
    RDY.InsertEnd(NewProcess);
}

ostream& operator<<(ostream& os, const FCFS& prcsr)
{
    os << "[FCFS]: " << prcsr.RDY.getCount() << " RDY: ";
    prcsr.RDY.PrintList();
    return os;
}