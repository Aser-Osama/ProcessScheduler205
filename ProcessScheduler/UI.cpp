#include "UI.h"

void UI::print_interactive(int c_ts, LinkedList<Processor*> processors, Queue<Process*> BLK, Queue<Process*> TRM)
{
	general_template(c_ts, processors, BLK, TRM);
	system("pause");
	system("cls");
}

void UI::print_sbs(int c_ts, LinkedList<Processor*> processors, Queue<Process*> BLK, Queue<Process*> TRM)
{
	general_template(c_ts, processors, BLK, TRM);
	Sleep(1000);
	system("cls");
	
}

void UI::general_template(int c_ts, LinkedList<Processor*>processors, Queue<Process*> BLK, Queue<Process*> TRM)
{	
	cout << "Current Timestep: " << c_ts << endl;
	cout << "----------------- RDY processes ----------------" << endl;
	int i = 1;
	Node<Processor*>* tmp_p = processors.getHead();
	while (tmp_p)
	{
		FCFS* FCFSPtr = dynamic_cast<FCFS*>(tmp_p->getItem());  
		SJF* SJFPtr = dynamic_cast<SJF*>(tmp_p->getItem()); 
		RR* RRPtr = dynamic_cast<RR*>(tmp_p->getItem());  
		if (FCFSPtr) {
			cout << "Processor " << i << ": \t" << *(FCFSPtr) << endl;
		}
		else if (SJFPtr) {
			cout << "Processor " << i << ": \t" << *(SJFPtr) << endl;
		}
		else if (RRPtr) {
			cout << "Processor " << i << ": \t" << *(RRPtr) << endl;
		}

		i++;
		tmp_p = tmp_p->getNext();
	}



	cout << "----------------- BLK processes ----------------" << endl;
	cout << BLK.getCount() << " BLK: ";
	BLK.Print();


	cout << "----------------- RUN processes ----------------" << endl;
	
	i = 1;
	tmp_p = processors.getHead();
	int run_cnt = 0;
	while (tmp_p)
	{
		if (tmp_p->getItem()->isBusy())
		{
			run_cnt++;
		}
		tmp_p = tmp_p->getNext();
	}

	tmp_p = processors.getHead();
	cout << run_cnt << " RUN: ";
	i = 1;
	while (tmp_p)
	{
		if (tmp_p->getItem()->isBusy())
		{
			cout << tmp_p->getItem()->getRUN() << "(P" << i << ")" << "\t";

		}
		i++;
		tmp_p = tmp_p->getNext();
	}
	cout << "\n";

	cout << "----------------- TRM processes ----------------" << endl;
	cout << TRM.getCount() << " TRM:" << "\t";
	TRM.Print();
}
