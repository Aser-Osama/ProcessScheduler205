#include "FCFS.h"

void FCFS::ScheduleAlgo() {
    Node<Process*>* nR; //the new process to be in run
    nR = RDY.getHead(); //the first element in rdy
    if (nR) { //if rdy is not null 
        setRUN(nR->getItem());
        RDY.DeleteFirst();
    }
    else { //if rdy is null
        setRUN(nullptr);
    }
}

void FCFS::SigKill(Process* P){
    //search for the the process in  the RUN or RDY list then move it TRM 
    //then calculate the statistics of the process like CT, etc.
}
Process* FCFS::findP(Process* P)
{
    if (P->getPID() == RUN->getPID())
    {
        //return clearRUN();
        return RUN;
    }
    else
    {
        Node<Process*>* tmp = RDY.getHead();
        bool found = false;
        while (tmp)
        {
            if (tmp->getItem()->getPID() == P->getPID())
            {
                Process* item = tmp->getItem();
                //RDY.DeleteNode(item);
                return item;
            }
            tmp = tmp->getNext();
        }
        return nullptr;
    }
}

Queue<Process*> FCFS::killOrphans(Process* P) {
    //P is the parent process that is already about to terminate
    Node<Process*>* Head = (P->getChildren()).getHead(); //the first child of P
    Node<Process*>* R = Head;
    Queue<Process*> Orphans;
        while (Head)
        {
            Orphans.enqueue(Head->getItem()); //add the child to orphans queue
            R = Head->getNext(); //get the next child 
            killOrphans(Head->getItem()); //now that the first child is about to be terminated we need to test if it has any children
            Head = R;
        } //kills all orphans
        
        //killOrphans should be called whenever any process is about to terminate
        // killOrphans should be always be called at sigKill to ensure that children, grandchildren,... are all killed recursively
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