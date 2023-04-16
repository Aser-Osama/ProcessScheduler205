#include "Scheduler.h"
#include "ADT/Linked_Queue/Queue.h"


using namespace std;

void test_print();

int main() {

	Scheduler ProcessScheduler;
	ProcessScheduler.load("testfile");
//	ProcessScheduler.run();
//	ProcessScheduler.save();

	test_print();



	return 0;
}


#include "Process.h"
#include "ADT/LinkedList.h"
#include "UI.h"
#include "Processors/Processor.h"
#include "Processors/FCFS.h"
#include "Processors/SJF.h"
void test_print() {

	Queue<Process*> rdy1;
	Queue<Process*> rdy2;

	Process p1(1);
	Process p2(2);
	Process p3(3);
	rdy1.enqueue(&p1);
	rdy1.enqueue(&p2);
	rdy1.enqueue(&p3);
	rdy1.enqueue(&p3);

	Process p11(11);
	Process p12(22);
	Process p13(33);
	rdy2.enqueue(&p11);
	rdy2.enqueue(&p12);
	rdy2.enqueue(&p13);

	//blk
	Process p4(4);
	Process p5(5);
	Process p6(6);
	Queue<Process> blk;
	blk.enqueue(p4);
	blk.enqueue(p5);
	blk.enqueue(p6);
	
	//trm
	Process p7(7);
	Process p8(8);
	Process p9(9);
	Queue<Process> trm;
	trm.enqueue(p7);
	trm.enqueue(p8);
	trm.enqueue(p9);



	LinkedList<Processor*> lst;
	FCFS fcfs1(rdy1);
	FCFS fcfs2(rdy1);
	FCFS fcfs3(rdy2);
	FCFS fcfs4(rdy1);
	FCFS fcfs5(rdy2);
	SJF SJF1(rdy2);
	SJF SJF2(rdy2);
	SJF SJF3(rdy1);
	SJF SJF4(rdy2);
	SJF SJF5(rdy2);
	lst.InsertEnd(&fcfs1);
	lst.InsertEnd(&fcfs2);
	lst.InsertEnd(&fcfs3);
	lst.InsertEnd(&fcfs4);
	lst.InsertEnd(&fcfs5);
	lst.InsertEnd(&SJF2);
	lst.InsertEnd(&SJF3);
	lst.InsertEnd(&SJF4);
	lst.InsertEnd(&SJF5);
	lst.InsertEnd(&SJF1);



	UI ui;
	cout << "testing interactive\n";
	for (int i = 0; i < 10; i++)
	{

		ui.print_interactive(i, lst, blk, trm);
		trm.enqueue(p9);
		blk.enqueue(p4);
		blk.enqueue(p5);

	}
	cout << "testing 1secdel\n";

	for (int i = 0; i < 10; i++)
	{

		ui.print_sbs(i, lst, blk, trm);
		trm.enqueue(p9);
		blk.enqueue(p4);
		blk.enqueue(p5);

	}
}