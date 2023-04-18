#include "RR.h"


//void RR::ScheduleAlgo(){
////    cout<<"this is RR schedule algo";
////    Process* nR;
////    if (RDY.dequeue(nR)) {
////        cout<<*nR<<"this is a process";
////        setRUN(nR);
////        RDY.enqueue(nR);
////    }
////    else {
////        setRUN(nullptr);
////    }
////    
//
//}

void RR::ScheduleAlgo() {
    //Process* nR;
    //if (RDY.dequeue(nR)) //if a there is a process* to dequeue from RDY into nR
    //{
    //    if (nR->getRemainingTime() <0) {
    //        setRUN(nR); //sets the RUN to the dequeued process*
    //        RDY.enqueue(nR); //enqueues the process* again
    //        cout << "\n1\n";
    //    }
    //    else if (nR->getRemainingTime() == 0) {
    //        setRUN(nR); //sets the RUN to the dequeued process* without enqueuing
    //        cout << "\n2\n";
    //    }
    //}
    //else {
    //    setRUN(nullptr);
    //    cout << "\n3\n";
    //}
    Process* nR;
    cout << "inside RR schedule algo";
    if (RDY.dequeue(nR)) { cout << "being set in schedule algo RR"; setRUN(nR); }
    else {
        setRUN(nullptr); cout << "being set as null";
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
			cout << "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT" << endl << current_rr_ts << "VS" << RR_SLICE;
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

	//cout<<"Execute function";
	//if (RUN) {
	//	cout<<"Inside the Run condition in executre function";
	//	if (RUN->getIO_R_D().getValue(crnt_ts, io_length)) //if this is the time step when the process asks for I/O
	//	{
	//	cout<<"Inside the Run condition in executre function 2";
	//		P = RUN; //returns the pointer the process for the scheduler to recieve and move to BLK
	//		ScheduleAlgo(); //calls the scheduling algorithim for the processor 
	//		return true; //informs the Scheduler that the process asked for I/O so it should be moved to BLK
	//	}
	//	else if (!RUN->subRemainingTime()) //if this is the last time step for the process
	//	{
	//	cout<<"Inside the Run condition in executre function 3";
	//		P = RUN; //returns the pointer the finished process for the scheduler to recieve and move to TRM
	//		ScheduleAlgo(); //calls the scheduling algorithim for the processor 
	//		return false; //informs the Scheduler that the process did not ask for I/O 
	//	}
	//	else //if this is not the last time step for the process and it does not ask for I/O
	//	{
	//	cout<<"Inside the Run condition in executre function 4";
	//		P = nullptr; //returns NULL to the Scheduler because no process will be moved
	//		return false; ////informs the Scheduler that the process did not ask for I/O 
	//	}
	//}
	//else
	//{
	//	cout<<"Inside the Run condition in executre else";
	//	ScheduleAlgo(); //calls the scheduling algorithim for the processor 
	//	P = nullptr; 
	//	return false;
	//}
}