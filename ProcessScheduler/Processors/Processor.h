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
    int currentBusyTime = 0; // Total time of each queue
    int totalIdleTime;
    int totalBusyTime;
    int totalTRT;
    bool Stop = false;
public:
    virtual void ScheduleAlgo() = 0; 
    virtual Process* getTopElem() = 0;
    virtual void moveToRDY(Process* const& NewProcess) = 0;
    int getIdleTime();
    int getBusyTime();
    void addTotalTRT(int);
    int getTotalTRT();
    bool isBusy(); 
    Process* getRUN();
    void setRUN(Process*);
    virtual bool Execute(Process*&, int, int&);
    virtual int getCurrentTime();
    Process* clearRUN();
    static Scheduler* getScheduler();


};  
