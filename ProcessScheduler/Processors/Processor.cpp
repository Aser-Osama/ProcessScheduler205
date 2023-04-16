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

Process* Processor::clearRun(){
    Process* temp = RUN;
    RUN=nullptr;
    return temp;
}

