#pragma once

#include "../ADT/LinkedList.h"
#include "../ADT/Linked_Queue/Queue.h"
#include "../ADT/Array_Stack/Stack.h"
#include "../ADT/PriorityQueue.h"
#include "../Process.h"

class Scheduler;

class Processor
{
    protected:
    static Scheduler* sch;
    Process* RUN;
    int currentBusyTime = 0;
    int totalIdleTime;
    int totalBusyTime;
public:
    virtual void ScheduleAlgo() = 0; 
    virtual Process* getTopElem() = 0;
    virtual void moveToRDY(Process* const& NewProcess) = 0;
    int getIdleTime();
    int getBusyTime();
    bool isBusy(); 
    Process* getRUN();
    void setRUN(Process*);
    virtual bool Execute(Process*&, int, int&);
    virtual int getCurrentTime();
    virtual int incrementCurrentTime(int);
    Process* clearRUN();
    static Scheduler* getScheduler();


};  
