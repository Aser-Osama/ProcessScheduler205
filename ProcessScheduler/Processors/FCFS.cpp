#include "FCFS.h"

void FCFS::SigKill(Process* P){
    //search for the the process in  the RUN or RDY list then move it TRM 
    //then calculate the statistics of the process like CT, etc.
}

void FCFS::ScheduleAlgo(){
    Process* nR;
    nR = RDY.getHead()->getItem();
    setRUN(nR);
    RDY.DeleteFirst();
}


  

void FCFS::removeFromReady(int pid)
{
    Node<Process*>* head = RDY.getHead();
    Process* to_remove;

    while (head)
    {
        if (head->getItem()->find_by_pid(pid))
        {
            to_remove = head->getItem();
            RDY.DeleteNode(to_remove);
            return; //assuming 2 processes cant have the same pid
        }
        else 
        {
            head = head->getNext();
        }
    }
    
}

FCFS::FCFS(){

}

void FCFS::moveToRDY(Process* NewProcess)
{
//    RDY.enqueue(NewProcess);
}

ostream& operator<<(ostream& os, const FCFS& prcsr)
{
    os << "[FCFS]: " << "prcsr.RDY.getCount()" << "RDY: ";
    prcsr.RDY.PrintList();
    return os;
}