#pragma once

#include "../ADT/LinkedList.h"
#include "../ADT/Linked_Queue/Queue.h"
#include "../ADT/Array_Stack/Stack.h"
#include "../ADT/PriorityQueue.h"
#include "../Process.h"

class Processor
{
    Process* RUN;
    int idleTime;
    int busyTime;
public:
    virtual void ScheduleAlgo() = 0; 
    virtual void moveToRDY(Process* const& NewProcess) = 0;
    int getIdleTime();
    int getBusyTime();
    bool isBusy(); 
    Process* getRUN();
    void setRUN(Process*);
    bool Execute(Process*&, int, int&);
    
    Process* clearRUN();

};  
