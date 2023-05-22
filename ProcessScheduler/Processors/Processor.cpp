#include "Processor.h"
#include "..\Scheduler.h"
int Processor::getBusyTime() {
	return this->totalBusyTime;
}
int Processor::getIdleTime() {
	return totalIdleTime;
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

void Processor::addTotalTRT(int add){
	totalTRT+=add;
}


int Processor::getTotalTRT() {
	return totalTRT;
}
bool Processor::Execute(Process*& P, int crnt_ts, int& io_length) {
	/*
		C1)True & PTR -> TRM (process done)
		C2)False & PTR -> TRM (IO request)
		C3)False & NULLPTR -> still executing
		ScheduleAlgo fills the RUN in case it's being cleared out or is already empty
	*/

	if (RUN) 
	{
		if (RUN->getIO_R_D().getValue(crnt_ts, io_length)) //if this is the timestep when the process asks for I/O
		{
			this->currentBusyTime--;
			P = RUN; //returns the pointer the process for the scheduler to recieve and move to BLK
			ScheduleAlgo(); //calls the scheduling algorithim for the processor 
			return false; //informs the Scheduler that the process asked for I/O so it should be moved to BLK //C2 (move to blk, io req)
		}
		else 
		{
			bool isDone = !(RUN->subRemainingTime());
			if (isDone)
			{
				P = RUN;
				ScheduleAlgo();
				return true;//C1 (complete Process, move to TRM)
			}
			else
			{
				this->currentBusyTime--;
				P = nullptr;
				return false; //C3 (still excuting)
			}
		}
	}
	else //no process currently running
	{
		P = nullptr;
		ScheduleAlgo();
		return false; //C3 (edge case)
	}
}

int Processor::getCurrentTime() {
	return this->currentBusyTime;
}


Scheduler* Processor::sch = new Scheduler("./testfile");

Scheduler* Processor::getScheduler()
{
	return sch;
}


