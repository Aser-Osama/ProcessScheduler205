#include "FCFS.h"

void FCFS::SigKill(Process* P){
    //search for the the process in  the RUN or RDY list then move it TRM 
    //then calculate the statistics of the process like CT, etc.
}

void FCFS::ScheduleAlgo(){
    Node<Process*>* nR;
    nR = RDY.getHead();
    if (nR) {
        setRUN(nR->getItem());
        RDY.DeleteFirst();
    }
    else {
        setRUN(nullptr);
    }
}

void FCFS::killOrphans(Process* P) {
    Node<Process*>* Head = (P->getChildren()).getHead();
    Node<Process*>* R = Head;
        while (Head)
        {
            R = Head->getNext();
            SigKill(Head->getItem());
            Head = R;
        } //kills all the children of the same parent
        // killOrphans should be always be called at sigKill to ensure that children, grandchildren,... are all killed
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