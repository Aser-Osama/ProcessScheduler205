#include "SJF.h"


void SJF::ScheduleAlgo(){

}

SJF::SJF(){

}

void SJF::MoveToRDY(Process* NewProcess)
{
    RDY.enqueue(NewProcess);
}