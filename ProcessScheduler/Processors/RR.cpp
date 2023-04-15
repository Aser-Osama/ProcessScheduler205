#include "RR.h"


void RR::ScheduleAlgo(){

}

RR::RR(int RRnum){

}
void RR::MoveToRDY(Process* NewProcess)
{
    RDY.enqueue(NewProcess);
}