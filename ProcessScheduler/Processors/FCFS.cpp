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
Process* FCFS::findProcess(int pid)
{
    if (pid == RUN->getPID())
    {
        return clearRUN();;
        //ScheduleAlgo();
    }
    else
    {
        Node<Process*>* tmp = RDY.getHead();
        bool found = false;
        while (tmp)
        {
            if (tmp->getItem()->getPID() == pid)
            {
                Process* item = tmp->getItem();
                RDY.DeleteNode(item);
                return item;
            }
            tmp = tmp->getNext();
        }
        return nullptr;
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