#include "FCFS.h"

void FCFS::SigKill(Process* P){
    //search for the the process in  the RUN or RDY list then move it TRM 
    //then calculate the statistics of the process like CT, etc.
}

void FCFS::ScheduleAlgo(){

}

FCFS::FCFS(){

}

void FCFS::MoveToRDY(Process* NewProcess)
{
    RDY.enqueue(NewProcess);
}