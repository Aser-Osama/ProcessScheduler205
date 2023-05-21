#include "Scheduler.h"

Scheduler::Scheduler(string filename) {
	this->load(filename);
	StartingPoint = Processors.getHead();
}
Scheduler::~Scheduler() {}



void Scheduler::Fill_Rdy()
{
	Queue<Process*> Arrived;
	if (NEW.isEmpty()) return;

	for (int i = 0; i < total_nprocess; i++)
	{
		Process* tmp;
		if (NEW.dequeue(tmp))
		{
			if (tmp->getAT() == timestep)
			{
				Arrived.enqueue(tmp);
			}
			else
			{
				NEW.enqueue(tmp);
			}
		}
	}

	Node<Processor*>* CPU_NODE = StartingPoint;
	while (!Arrived.isEmpty())
	{
		Process* tmp;
		Arrived.dequeue(tmp);
		if (tmp)
			(CPU_NODE->getItem())->moveToRDY(tmp);

		if (CPU_NODE->getNext())
		{
			CPU_NODE = CPU_NODE->getNext();
		}
		else // If there is no next node, set the node to the head of the list
		{
			CPU_NODE = Processors.getHead();
		}
	}
	StartingPoint = CPU_NODE;
}


void Scheduler::BLKToRun(Processor* const& prcsr)
{
	int rnum = (rand() % 100) + 1;
	if (rnum > 10) return;

	Process* first_elm;
	bool dequed = BLK.dequeue(first_elm);
	if (dequed) { prcsr->moveToRDY(first_elm); }
}

void Scheduler::randomizeRUN(Processor* const& prcsr)
{ //should be run before the SCHEDULINGALGO function so 
	//rdy wont be left empty a whole cycle in case the
	//function activates.
	int rnum = (rand() % 100) + 1;
	if (rnum >= 1 && rnum <= 15)
	{
		Process* ptr = prcsr->clearRUN();
		if (ptr)
		{
			BLK.enqueue(ptr);
		}
	}
	else if (rnum >= 20 && rnum <= 30)
	{
		Process* ptr = prcsr->clearRUN();
		if (ptr) {
			prcsr->moveToRDY(ptr);
		}
	}
	else if (rnum >= 50 && rnum <= 60)
	{
		Process* ptr = prcsr->clearRUN();
		if (ptr)
		{
			TRM.enqueue(ptr);
		}
	}
}

void Scheduler::randomKill(Processor* const& prcsr)
{
	FCFS* fcfs_ptr = dynamic_cast<FCFS*>(prcsr);
	if (!fcfs_ptr) return;

	int rnum = (rand() % total_nprocess) + 1;
	Process* tmp = fcfs_ptr->removeFromReady(rnum);

	if (tmp) TRM.enqueue(tmp);
}

void Scheduler::randomizeBLK(Processor* const& prcsr)
{
	int rnum = (rand() % 100) + 1;
	if (rnum > 10) return;

	Process* first_elm;
	bool dequed = BLK.dequeue(first_elm);
	if (dequed) { prcsr->moveToRDY(first_elm); }
}

Map<int, int> Scheduler::parseIO_R_D(string input) {
	Map<int, int> output;
	bool mode = 0;
	string k, v;

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == '(') {
			k = "";
			v = "";
		}
		else if (input[i] == ',') {
			mode = !mode;
		}
		else if (input[i] == ')') {
			output.addPair(stoi(k), stoi(v));
		}
		else {
			if (mode)
				v += input[i];
			else
				k += input[i];
		}

	}
	return output;
}

void Scheduler::load(string fileName) {
	ifstream file;
	file.open(fileName);
	int NF, NS, NR, RRSlice;
	file >> NF; file >> NS; file >> NR; file >> RRSlice;

	for (int i = 0; i < NF; i++) {
		FCFS* temp = new FCFS();
		Processors.InsertEnd(temp);
	}
	for (int i = 0; i < NS; i++) {
		SJF* temp = new SJF();
		Processors.InsertEnd(temp);
	}

	for (int i = 0; i < NR; i++) {
		RR* temp = new RR(RRSlice);
		Processors.InsertEnd(temp);
	}
	file >> RTF; file >> MaxW; file >> STL; file >> forkProb;

	int ProcessCount;
	file >> ProcessCount;

	for (int i = 0; i < ProcessCount; i++) {
		int AT, PID, CT, N;
		string IO_R_D_unparsed;
		file >> AT; file >> PID; file >> CT; file >> N;
		if (N != 0)file >> IO_R_D_unparsed;
		Map<int, int> IO_R_D;
		IO_R_D = parseIO_R_D(IO_R_D_unparsed);
		Process* temp = new Process(PID, AT, CT, IO_R_D);
		NEW.enqueue(temp);
	}

	while (!file.eof()) {
		int time, PID;
		file >> time; file >> PID;
		SIGKILL.addPair(time, PID);
	}

	total_nprocess = NEW.getCount();
	ncpu = NR + NF + NS;
}

void Scheduler::run()
{
	bool proccess_complete;
	Process* tmp_prcs;
	int io_time = -1; //there is no io in this phase
	while (TRM.getCount() < total_nprocess) //will be "while all not in trm"
	{
		Node<Processor*>* CPU_node = Processors.getHead();
		this->Fill_Rdy();
		while (CPU_node)
		{
			proccess_complete = (CPU_node->getItem())->Execute(tmp_prcs, timestep, io_time);
			if (proccess_complete && tmp_prcs) this->TRM.enqueue(tmp_prcs);
			if (!proccess_complete && tmp_prcs) this->BLK.enqueue(tmp_prcs);

			this->randomizeRUN(CPU_node->getItem());
			this->randomizeBLK(CPU_node->getItem());
			this->randomKill(CPU_node->getItem());

			CPU_node = CPU_node->getNext();
		}



		MAIN_UI.print_interactive(true,timestep, Processors, BLK, TRM); // the print type will be based on user choice in phase 2
		timestep++;

	}
	MAIN_UI.print_interactive(false, timestep, Processors, BLK, TRM); // the print type will be based on user choice in phase 2

}