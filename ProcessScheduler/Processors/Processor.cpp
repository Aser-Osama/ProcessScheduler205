#include "Processor.h"

int Processor::getBusyTime() {
	return busyTime;
}
int Processor::getIdleTime() {
	return idleTime;
}

bool Processor::isBusy() {
	return !(RUN == nullptr);
}

Process* Processor::getRUN() {
	return RUN;
}

void Processor::setRUN(Process* P) {
	RUN = P;
}

Process* Processor::clearRUN() {
	Process* temp = RUN;
	RUN = nullptr;
	return temp;
}


bool Processor::Execute(Process*& P, int crnt_ts, int& io_length) {
	if (RUN) {
		if (RUN->getIO_R_D().getValue(crnt_ts, io_length)) //if this is the time step when the process asks for I/O
		{
			P = RUN; //returns the pointer the process for the scheduler to recieve and move to BLK
			ScheduleAlgo(); //calls the scheduling algorithim for the processor 
			return true; //informs the Scheduler that the process asked for I/O so it should be moved to BLK
		}
		else if (!RUN->subRemainingTime()) //if this is the last time step for the process
		{
			P = RUN; //returns the pointer the finished process for the scheduler to recieve and move to TRM
			ScheduleAlgo(); //calls the scheduling algorithim for the processor 
			return false; //informs the Scheduler that the process did not ask for I/O 
		}
		else //if this is not the last time step for the process and it does not ask for I/O
		{
			P = nullptr; //returns NULL to the Scheduler because no process will be moved
			return false; ////informs the Scheduler that the process did not ask for I/O 
		}
	}
	else
	{
		P = nullptr; 
		return false;
	}
}