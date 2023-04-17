#include "Scheduler.h"

Scheduler::Scheduler(string filename) {
	this->load(filename);
}
Scheduler::~Scheduler() {}


void Scheduler::Initialize_RDY()
{
	bool flag = false;
	Node<Processor*>* cur_CPU = Processors.getHead();
	Node<Processor*>* fir_CPU = Processors.getHead();
	int iter = 0; 
	int tot = total_nprocess;
	while (!NEW.isEmpty() && iter < tot)
	{
		Process* process;
		NEW.dequeue(process);
		if (cur_CPU->getNext() != nullptr)
		{
			if (process->getAT() == timestep)
			{
				cur_CPU->getItem()->moveToRDY(process);
			}
			else
			{
				NEW.enqueue(process);
			}
			cur_CPU = cur_CPU->getNext();
		}
		else
		{
			if (!flag)
			{
				cur_CPU->setNext(fir_CPU);
				flag = true;
			}
			if (process->getAT() == timestep)
			{
				cur_CPU->getItem()->moveToRDY(process);
				
			}
			else
			{
				NEW.enqueue(process);
			}
			cur_CPU = cur_CPU->getNext();
		}
		iter++;
	}

}

void Scheduler::simulator()
{
	int t = 0;
	int c = 0;
	Node<Processor*>* CPU_node = Processors.getHead();
	Node<Processor*>* HEAD_Node = Processors.getHead();

	bool flag;
	while (CPU_node->getNext()->getItem())
	{
		this->Initialize_RDY();
		Process* tmp_prcs;
		Processor* cpu_ptr = CPU_node->getItem();

		flag = (cpu_ptr)->Execute(tmp_prcs, timestep, t);
		if (flag && tmp_prcs) this->BLK.enqueue(tmp_prcs);
		if (!flag && tmp_prcs) this->TRM.enqueue(tmp_prcs);

		this->randomizeRUN(CPU_node->getItem());
		this->randomizeBLK(CPU_node->getItem());
		this->randomKill(CPU_node->getItem());

		MAINUI.print_interactive(timestep, Processors, BLK, TRM);
		cout << "\n";
		NEW.Print();
		cout << "\n";
		if (c != ncpu-2) {
			CPU_node = CPU_node->getNext();
			c++;
		}
		else {
			CPU_node = Processors.getHead();
			c = 0;
		}
		timestep++;
	}

}

void Scheduler::randomizeRUN(Processor* const& prcsr)
{ //should be run before the SCHEDULINGALGO function so 
	//rdy wont be left empty a whole cycle in case the
	//function activates.
	int rnum = (rand() % 100) + 1;
	if (rnum >= 1 && rnum <= 15)
	{
		Process* ptr = prcsr->clearRUN();
		if (ptr) { BLK.enqueue(ptr); cout << "BLK"; }
	}
	else if (rnum >= 20 && rnum <= 30)
	{
		Process* ptr = prcsr->clearRUN();
		if (ptr) { prcsr->moveToRDY(prcsr->clearRUN()); cout << "???"; }
		
	}
	else if (rnum >= 50 && rnum <= 60)
	{
		Process* ptr = prcsr->clearRUN();
		if (ptr) { TRM.enqueue(ptr); cout << "TRM"; }
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