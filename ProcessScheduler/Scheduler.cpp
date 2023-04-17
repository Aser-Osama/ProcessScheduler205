#include "Scheduler.h"

Scheduler::Scheduler(){}
Scheduler::~Scheduler(){}


void Scheduler::simulator(string fileName)
{
    bool flag = false;
    Node<Processor*>* temp = Processors.getHead();
    Node<Processor*>* FirstNode = Processors.getHead();
    load(fileName);
    while (!NEW.isEmpty())
    {
        Process* process;
        NEW.dequeue(process);
        if (temp->getNext() != nullptr)
        {
            temp->getItem()->moveToRDY(process);
            temp = temp->getNext();
        }
        else
        {
            if (!flag)
            {
                temp->setNext(FirstNode);
                flag = true;
            } 
            temp->getItem()->moveToRDY(process);
        }
    }

}

void Scheduler::randomizeRUN(Processor* const &prcsr)
{ //should be run before the SCHEDULINGALGO function so 
    //rdy wont be left empty a whole cycle in case the
    //function activates.
    int rnum = (rand() % 100) + 1;
    if (rnum >=1 && rnum <= 15)
    {
        BLK.enqueue(prcsr->clearRUN());
    }
    else if (rnum >= 20 && rnum <= 30)
    {
        prcsr->moveToRDY(prcsr->clearRUN());
    }
    else if (rnum >= 50 && rnum <= 60)
    {
        TRM.enqueue(prcsr->clearRUN());
    }
}

void Scheduler::randomKill(Processor* const& prcsr)
{
    FCFS* fcfs_ptr = dynamic_cast<FCFS*>(prcsr);
    if (!fcfs_ptr) return;
    
    int rnum = (rand() % total_nprocess) + 1;
    fcfs_ptr->removeFromReady(rnum);
}

void Scheduler::randomizeBLK(Processor* const& prcsr)
{
    int rnum = (rand() % 100) + 1;
    if (rnum > 10) return;

    Process* first_elm;
    bool dequed = TRM.dequeue(first_elm);
    if (dequed) { prcsr->moveToRDY(first_elm); }
}

Map<int,int> Scheduler::parseIO_R_D(string input){
    Map<int,int> output;
    bool mode=0;
    string k, v;

    for (int i=0; i<input.length();i++){
        if (input[i]=='('){
            k="";
            v="";
        }
        else if (input[i]==','){
            mode=!mode;
        }
        else if(input[i]==')'){
            output.addPair(stoi(k),stoi(v));
        }
        else{
            if (mode)
                v+=input[i];
            else
                k+=input[i];
        }

    }
    return output;
}

void Scheduler::load(string fileName){
    ifstream file;
    file.open(fileName);
    int NF, NS, NR, RRSlice;
    file>>NF; file>>NS; file>>NR; file>>RRSlice;

    for (int i=0; i<NF; i++){ 
        FCFS * temp = new FCFS();
        Processors.InsertEnd(temp); 
        }
    for (int i=0; i<NS; i++){ 
        SJF * temp = new SJF();
        Processors.InsertEnd(temp); 
        }
 
    for (int i=0; i<NR; i++){ 
        RR * temp = new RR(RRSlice);
        Processors.InsertEnd(temp); 
        }
    file>>RTF; file>>MaxW; file>>STL; file>>forkProb;

    int ProcessCount;
    file>>ProcessCount;

    for (int i=0; i<ProcessCount; i++){ 
        int AT, PID, CT, N;
        string IO_R_D_unparsed;
        file>>AT; file>>PID; file>>CT; file>>N;
        if (N!=0)file>>IO_R_D_unparsed;
        Map<int, int> IO_R_D;
        IO_R_D=parseIO_R_D(IO_R_D_unparsed);
        Process* temp = new Process(PID,AT,CT,IO_R_D);
        NEW.enqueue(temp); 
        } 

    while (!file.eof()){
        int time, PID;
        file>>time; file>>PID;
        SIGKILL.addPair(time,PID);
    }

    total_nprocess = NEW.getCount();
}