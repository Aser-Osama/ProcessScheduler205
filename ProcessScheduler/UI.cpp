#include "UI.h"

void UI::print_interactive(int c_ts, LinkedList<Processor*> processors, Queue<Process> BLK, Queue<Process> TRM)
{
	general_template(c_ts, processors, BLK, TRM);
	system("pause");
}

void UI::print_sbs(int c_ts, LinkedList<Processor*> processors, Queue<Process> BLK, Queue<Process> TRM)
{
	general_template(c_ts, processors, BLK, TRM);
	Sleep(1000);
}

void UI::general_template(int c_ts, LinkedList<Processor*>processors, Queue<Process> BLK, Queue<Process> TRM)
{	
	cout << "Current Timestep: " << c_ts << endl;
	cout << "----------------- RDY processes ----------------" << endl;
	int i = 1;
	Node<Processor*>* tmp_p = processors.getHead();
	while (tmp_p)
	{
		cout << "Processor " << i << tmp_p->getItem();
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
			cout << tmp_p->getItem()->getRun() << "(P" << i << ")" << "\t";

		}
		i++;
		tmp_p = tmp_p->getNext();
	}
	cout << "\n";

	cout << "----------------- TRM processes ----------------" << endl;
	cout << TRM.getCount() << "\t";
	TRM.Print();
}
