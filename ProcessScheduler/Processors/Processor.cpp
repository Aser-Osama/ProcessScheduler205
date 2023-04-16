#include "Processor.h"

int Processor::getBusyTime(){
    return busyTime;
}
int Processor::getIdleTime(){
    return idleTime;
}

bool Processor::isBusy(){
    return !(RUN == nullptr);
}

Process* Processor::getRun(){
    return RUN;
}



