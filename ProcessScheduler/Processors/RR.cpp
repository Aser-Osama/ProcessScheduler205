#include "RR.h"

void RR::ScheduleAlgo() {
    Process* nR;
    if (RDY.dequeue(nR)) { setRUN(nR); }
    else {
        setRUN(nullptr); 
    }
}

RR::RR(int RRnum){
    RR_SLICE = RRnum - 1;
}

void RR::moveToRDY(Process* const& NewProcess)
{
    RDY.enqueue(NewProcess);
	current_rr_ts = 0;
}

ostream& operator<<(ostream& os, const RR& prcsr)
{
    os << "[RR]: " << prcsr.RDY.getCount() << " RDY: ";
    prcsr.RDY.Print();
    return os;
}

bool RR::Execute(Process*& P, int crnt_ts, int& io_length) {
	/*
		C1)True & PTR -> TRM (process done)
		C2)False & PTR -> TRM (IO request)
		C3)False & NULLPTR -> still excuting
		ScheduleAlgo fills the RUN in case its being cleared out or is already empty
	*/
	if (RUN) 
	{
		if (RUN->getIO_R_D().getValue(crnt_ts, io_length)) //if this is the time step when the process asks for I/O
		{
			P = RUN; //returns the pointer the process for the scheduler to recieve and move to BLK
			ScheduleAlgo(); //calls the scheduling algorithim for the processor
            current_rr_ts++; 
			return false; //informs the Scheduler that the process asked for I/O so it should be moved to BLK //C2 (move to blk, io req)
		}
		else 
		{
			bool isDone = !(RUN->subRemainingTime());
            if (current_rr_ts == RR_SLICE)
            {
                moveToRDY(RUN);
                ScheduleAlgo();
                P = nullptr;
                current_rr_ts = 0;
                return false;

            }
			else if (isDone)
			{
				P = RUN;
				ScheduleAlgo();
                current_rr_ts++;
				return true;//C1 (complete Process, move to TRM)

			}
			else
			{
				P = nullptr;
                current_rr_ts++;
				return false; //C3 (still excuting)
			}
		}
	}
	else //no process currently running
	{
		P = nullptr;
		ScheduleAlgo();
        current_rr_ts++;
		return false; //C3 (edge case)
	}
}