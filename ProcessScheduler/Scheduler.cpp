#include "Scheduler.h"

Scheduler::Scheduler(string filename)
{
	this->load(filename);
	StartingPoint = Processors.getHead();
}
Scheduler::~Scheduler() {}


void Scheduler::Fill_Rdy()
{
	Queue<Process *> Arrived;
	if (NEW.isEmpty())
		return;

	for (int i = 0; i < total_nprocess; i++)
	{
		Process *tmp;
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

	Node<Processor *> *cpuNode = StartingPoint;
	while (!Arrived.isEmpty())
	{
		Process *tmp;
		Arrived.dequeue(tmp);
		if (tmp)
			(cpuNode->getItem())->moveToRDY(tmp);

		if (cpuNode->getNext())
		{
			cpuNode = cpuNode->getNext();
		}
		else // If there is no next node, set the node to the head of the list
		{
			cpuNode = Processors.getHead();
		}
	}
	StartingPoint = cpuNode;
}

void Scheduler::randomizeRUN(Processor *const &prcsr)
{ // should be run before the SCHEDULINGALGO function so
	// rdy wont be left empty a whole cycle in case the
	// function activates.
	int rnum = (rand() % 100) + 1;
	if (rnum >= 1 && rnum <= 15)
	{
		Process *ptr = prcsr->clearRUN();
		if (ptr)
		{
			BLK.enqueue(ptr);
		}
	}
	else if (rnum >= 20 && rnum <= 30)
	{
		Process *ptr = prcsr->clearRUN();
		if (ptr)
		{
			prcsr->moveToRDY(ptr);
		}
	}
	else if (rnum >= 50 && rnum <= 60)
	{
		Process *ptr = prcsr->clearRUN();
		if (ptr)
		{
			TRM.enqueue(ptr);
		}
	}
}

void Scheduler::randomKill(Processor *const &prcsr)
{
	FCFS *fcfs_ptr = dynamic_cast<FCFS *>(prcsr);
	if (!fcfs_ptr)
		return;

	int rnum = (rand() % total_nprocess) + 1;
	Process *tmp = fcfs_ptr->removeFromReady(rnum);

	if (tmp)
		TRM.enqueue(tmp);
}

void Scheduler::randomizeBLK(Processor *const &prcsr)
{
	int rnum = (rand() % 100) + 1;
	if (rnum > 10)
		return;

	Process *first_elm;
	bool dequed = BLK.dequeue(first_elm);
	if (dequed)
	{
		prcsr->moveToRDY(first_elm);
	}
}

Map<int, int> Scheduler::parseIO_R_D(string input)
{
	Map<int, int> output;
	bool mode = 0;
	string k, v;

	for (int i = 0; i < input.length(); i++)
	{
		if (input[i] == '(')
		{
			k = "";
			v = "";
		}
		else if (input[i] == ',')
		{
			mode = !mode;
		}
		else if (input[i] == ')')
		{
			output.addPair(stoi(k), stoi(v));
		}
		else
		{
			if (mode)
				v += input[i];
			else
				k += input[i];
		}
	}
	return output;
}

void Scheduler::load(string fileName)
{
	ifstream file;
	file.open(fileName);
	int NF, NS, NR, RRSlice;
	file >> NF;
	file >> NS;
	file >> NR;
	file >> RRSlice;
	
	for (int i = 0; i < NF; i++)
	{
		FCFS *temp = new FCFS();
		Processors.InsertEnd(temp);
	}
	for (int i = 0; i < NS; i++)
	{
		SJF *temp = new SJF();
		Processors.InsertEnd(temp);
	}

	for (int i = 0; i < NR; i++)
	{
		RR *temp = new RR(RRSlice);
		Processors.InsertEnd(temp);
	}
	file >> RTF;
	file >> MaxW;
	file >> STL;
	file >> forkProb;

	int ProcessCount;
	file >> ProcessCount;

	for (int i = 0; i < ProcessCount; i++)
	{
		int AT, PID, CT, N;
		string IO_R_D_unparsed;
		file >> AT;
		file >> PID;
		file >> CT;
		file >> N;
		if (N != 0)
			file >> IO_R_D_unparsed;
		Map<int, int> IO_R_D;
		IO_R_D = parseIO_R_D(IO_R_D_unparsed);
		Process *temp = new Process(PID, AT, CT, IO_R_D);
		NEW.enqueue(temp);
	}

	while (!file.eof())
	{
		int time, PID;
		file >> time;
		file >> PID;
		SIGKILL.addPair(time, PID);
	}

	total_nprocess = NEW.getCount();
	ncpu = NR + NF + NS;
}

void Scheduler::run()
{
	bool proccess_complete;
	Process *tmp_prcs;
	int io_time = -1;						// there is no io in this phase
	while (TRM.getCount() < total_nprocess) // will be "while all not in trm"
	{
		Node<Processor *> *cpuNode = Processors.getHead();
		this->Fill_Rdy();
		while (cpuNode)
		{
			stealTask();
			proccess_complete = (cpuNode->getItem())->Execute(tmp_prcs, timestep, io_time);
			if (proccess_complete && tmp_prcs)
				this->TRM.enqueue(tmp_prcs);
			if (!proccess_complete && tmp_prcs)
				this->BLK.enqueue(tmp_prcs);
			//this->randomizeRUN(cpuNode->getItem());
			//this->randomizeBLK(cpuNode->getItem());
			//this->randomKill(cpuNode->getItem());

			cpuNode = cpuNode->getNext();
		}

		MAIN_UI.print_interactive(true, timestep, Processors, BLK, TRM); // the print type will be based on user choice in phase 2
		timestep++;
	}
	MAIN_UI.print_interactive(false, timestep, Processors, BLK, TRM); // the print type will be based on user choice in phase 2
}

void Scheduler::stealTask() //Function will be called every timestep
{

	if (timestep% STL != 0 || timestep == 0) { return; }
	
    int maxTime = -1;
    int minTime = (std::numeric_limits<int>::max)();
    Node<Processor *> *cpuNode = Processors.getHead();
    Processor *minCpu = nullptr;
    Processor *maxCpu = nullptr;

    while (cpuNode)
    {
        if (cpuNode->getItem()->getCurrentTime() > maxTime)
        {
            maxTime = cpuNode->getItem()->getCurrentTime();
            maxCpu = cpuNode->getItem();
        }
        if (cpuNode->getItem()->getCurrentTime() < minTime)
        {
            minTime = cpuNode->getItem()->getCurrentTime();
            minCpu = cpuNode->getItem();
        }
        cpuNode = cpuNode->getNext();
    }

	while ((static_cast<float>(maxTime - minTime) / maxTime) > 0.4)
    {
        if (minCpu != nullptr && maxCpu != nullptr && maxCpu != minCpu)
        {
            Process *process = maxCpu->getTopElem();
			if (!process) { return; }
            minCpu->moveToRDY(process);
            maxTime = maxCpu->getCurrentTime();
            minTime = minCpu->getCurrentTime();
			cout << "task being stolen \n\n\n\n";
        }
		else { return; }
    }
}

//void Scheduler::stealTask() //Function will be called every timestep
//{
//	if (timestep % STL != 0 || timestep == 0) { return; }
//
//	int maxTime = -1;
//	int minTime = (std::numeric_limits<int>::max)();
//	Node<Processor*>* cpuNode = Processors.getHead();
//	Processor* minCpu = nullptr;
//	Processor* maxCpu = nullptr;
//
//	while (cpuNode)
//	{
//		Processor* currentCpu = cpuNode->getItem();
//		if (currentCpu && currentCpu->getCurrentTime() > maxTime)
//		{
//			maxTime = currentCpu->getCurrentTime();
//			maxCpu = currentCpu;
//		}
//		if (currentCpu && currentCpu->getCurrentTime() < minTime)
//		{
//			minTime = currentCpu->getCurrentTime();
//			minCpu = currentCpu;
//		}
//		cpuNode = cpuNode->getNext();
//	}
//
//	while (maxCpu && minCpu && (static_cast<float>(maxTime - minTime) / maxTime) > 0.4)
//	{
//		if (maxCpu != minCpu)
//		{
//			Process* process = maxCpu->getTopElem();
//			if (process)
//			{
//				minCpu->moveToRDY(process);
//				maxTime = maxCpu->getCurrentTime();
//				minTime = minCpu->getCurrentTime();
//				cout << "task being stolen \n\n\n\n";
//			}
//			else { return; }
//		}
//		else { return; }
//	}
//}

bool Scheduler::migratedMaxW(Process* const& prcs)
{
	if (!prcs) {return false;}
    int ct = prcs->getCT();
	if (ct < this->MaxW) {return false;} //find a rr queue
	bool foundRR = false;
	Node<Processor *> *cpuNode = Processors.getHead();
	while (cpuNode)
	{
		Processor* prcsr = cpuNode->getItem();
		if (!prcsr) { return false; }
		RR *rr_ptr = dynamic_cast<RR*>(prcsr);
		if (!rr_ptr) { cpuNode = cpuNode->getNext(); continue; }
		rr_ptr->moveToRDY(prcs);
		foundRR = true;
		break;
	}
	if (foundRR) { cout << "RR migration found\t" << prcs->getPID() <<"\n\n\n"; }
	return foundRR;
}

bool Scheduler::migratedRTF(Process* const &prcs) //checks cpu_time under rft (Threshold) 
 {
	if (!prcs) {return false;}
    int ct = prcs->getCT();
	if (ct > this->RTF) {return false;} //find a sjf queue
	bool foundSJF = false;

	Node<Processor *> *cpuNode = Processors.getHead();
 	while (cpuNode)
	{
		Processor* prcsr = cpuNode->getItem();
		if (!prcsr) { return false; }
		SJF* sjf_ptr = dynamic_cast<SJF*>(prcsr);
		if (!sjf_ptr) { cpuNode = cpuNode->getNext();  continue; }
		prcsr->moveToRDY(prcs);
		foundSJF = true;
		break;
	}
	if (foundSJF) { cout << "SJF migration found \t" << prcs->getPID()<<" \n\n\n"; }
	return foundSJF;
}
