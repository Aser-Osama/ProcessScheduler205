#include "Scheduler.h"

Scheduler::Scheduler(string filename)
{
	this->load(filename);
	StartingPoint = Processors.getHead();
}
Scheduler::~Scheduler() {}

//void Scheduler::Fill_Rdy()
//{
//	Queue<Process *> Arrived;
//	if (NEW.isEmpty())
//		return;
//
//	for (int i = 0; i < total_nprocess; i++)
//	{
//		Process *tmp;
//		if (NEW.dequeue(tmp))
//		{
//			if (tmp->getAT() == timestep)
//			{
//				Arrived.enqueue(tmp);
//			}
//			else
//			{
//				NEW.enqueue(tmp);
//			}
//		}
//	}
//
//	Node<Processor *> *processorNode = StartingPoint;
//	while (!Arrived.isEmpty())
//	{
//		Process *tmp;
//		Arrived.dequeue(tmp);
//		if (tmp) {
//			tmp->setCpuArrivalTime(timestep);
//			(processorNode->getItem())->moveToRDY(tmp);
//		}
//
//		if (processorNode->getNext())
//		{
//			processorNode = processorNode->getNext();
//		}
//		else // If there is no next node, set the node to the head of the list
//		{
//			processorNode = Processors.getHead();
//		}
//	}
//	StartingPoint = processorNode;
//}

//void Scheduler::Fill_Rdy()
//{
//	Queue<Process*> Arrived;
//	Process* tmp;
//	Process* tmpa;
//
//	if (NEW.isEmpty())
//		return;
//
//	int notArrivedCount = NEW.getCount();  // Store the initial count of processes in NEW queue
//
//	for (int i = 0; i < notArrivedCount; i++)
//	{
//		Process* tmpa;
//		if (NEW.dequeue(tmpa))
//		{
//			if (tmpa->getAT() == timestep)
//			{
//				Arrived.enqueue(tmpa);
//			}
//			else
//			{
//				NEW.enqueue(tmpa);
//			}
//		}
//	}
//
//
//	while (Arrived.dequeue(tmp))
//	{
//		if (!tmp) { break; }
//		Node<Processor*>* processorNode = Processors.getHead();
//		Processor* minProcessor = nullptr;
//		int minTime = INT_MAX;
//
//		while (processorNode)
//		{
//			Processor* tempProcessor = processorNode->getItem();
//			if (!tempProcessor)
//			{
//				processorNode = processorNode->getNext();
//				continue;
//			}
//
//			if ((processorNode->getItem()->getCurrentTime() < minTime))
//			{
//				minTime = processorNode->getItem()->getCurrentTime();
//				minProcessor = processorNode->getItem();
//			}
//
//			processorNode = processorNode->getNext();
//		}
//
//		if (minProcessor) {
//			tmp->setRT(timestep);
//			tmp->setCpuArrivalTime(timestep);
//			minProcessor->moveToRDY(tmp);
//		}
//		else {
//			Arrived.enqueue(tmp);
//		}
//	}
//}

void Scheduler::NEWToRDY()
{
	Process* Process = nullptr;
	Node<Processor*>* ProcessorWithShortestQueue = nullptr;
	// If there is a process in the NEW list and its arrival time equals the currnent timestep
	while (NEW.peek(Process) && Process->getAT() == timestep)
	{
		NEW.dequeue(Process);
		Node<Processor*>* tempProcessor1 = Processors.getHead(); // Gets the first processor from the Linked list
		ProcessorWithShortestQueue = tempProcessor1;

		Node<Processor*>* tempProcessor2 = tempProcessor1->getNext();
		if (!tempProcessor2) return; // Checks if the list has two or more processors to compare between them

		while (tempProcessor2->getNext())
		{
			if (ProcessorWithShortestQueue->getItem()->getCurrentTime() > tempProcessor2->getItem()->getCurrentTime())
			{
				ProcessorWithShortestQueue = tempProcessor2;
			}
			tempProcessor2 = tempProcessor2->getNext();
		}
		// while loop stops at the last processor.
		// So, a comparison must be made between the last processor and ShortestQueue

		if (ProcessorWithShortestQueue->getItem()->getCurrentTime() > tempProcessor2->getItem()->getCurrentTime())
			ProcessorWithShortestQueue = tempProcessor2;

		ProcessorWithShortestQueue->getItem()->moveToRDY(Process);
		Process = nullptr;
	}
}

void Scheduler::BLKToRDY(Processor* const& prcsr)
{
	Process* first_elm;
	bool dequed = BLK.dequeue(first_elm);
	if (dequed) { 
		prcsr->moveToRDY(first_elm);
	}
}

void Scheduler::randomizeRUN(Processor* const& prcsr)
{ // should be run before the SCHEDULINGALGO function so
	// rdy wont be left empty a whole cycle in case the
	// function activates.
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
		if (ptr)
		{
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
	if (!fcfs_ptr)
		return;

	int rnum = (rand() % total_nprocess) + 1;
	Process* tmp = fcfs_ptr->removeFromReady(rnum);

	if (tmp)
		TRM.enqueue(tmp);
}

void Scheduler::randomizeBLK(Processor* const& prcsr)
{
	int rnum = (rand() % 100) + 1;
	if (rnum > 10)
		return;

	Process* first_elm;
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
		FCFS* temp = new FCFS();
		Processors.InsertEnd(temp);
	}
	for (int i = 0; i < NS; i++)
	{
		SJF* temp = new SJF();
		Processors.InsertEnd(temp);
	}

	for (int i = 0; i < NR; i++)
	{
		RR* temp = new RR(RRSlice);
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
		Process* temp = new Process(PID, AT, CT, IO_R_D);
		NEW.enqueue(temp);
	}

	while (!file.eof())
	{
		int time, PID;
		file >> time;
		file >> PID;
		SIGKILL_MAP.addPair(time, PID);
	}

	total_nprocess = NEW.getCount();
	total_notarrived = NEW.getCount();
	nprocessor = NR + NF + NS;
}

void Scheduler::run()
{

	bool proccess_complete;
	Process* tmp_prcs;
	int io_time = -1;						// there is no io in this phase
	while (TRM.getCount() < total_nprocess) // will be "while all not in trm"
	{
		Node<Processor*>* processorNode = Processors.getHead();
		this->NEWToRDY();
		int i = 1;
		while (processorNode)
		{
			stealTask();
			killSignal();
			proccess_complete = (processorNode->getItem())->Execute(tmp_prcs, timestep, io_time);
			if (proccess_complete && tmp_prcs)
			{
				tmp_prcs->setTT(timestep);
				tmp_prcs->setTRT();
				tmp_prcs->setWT();
				this->TRM.enqueue(tmp_prcs);
			}
			if (!proccess_complete && tmp_prcs) {

				this->BLK.enqueue(tmp_prcs);
			}
			// this->randomizeRUN(processorNode->getItem());
			// this->randomizeBLK(processorNode->getItem());
			// this->randomKill(processorNode->getItem());
			processorNode = processorNode->getNext();
		}

		MAIN_UI.print_interactive(true, timestep, Processors, BLK, TRM); // the print type will be based on user choice in phase 2
		timestep++;
	}
	MAIN_UI.print_interactive(false, timestep, Processors, BLK, TRM); // the print type will be based on user choice in phase 2
}

void Scheduler::stealTask() // Function will be called every timestep
{

	if (timestep % STL != 0 || timestep == 0)
	{
		return;
	}

	int maxTime = INT_MIN;
	int minTime = INT_MAX;
	Node<Processor*>* processorNode = Processors.getHead();
	Processor* minprocessor = nullptr;
	Processor* maxprocessor = nullptr;

	while (processorNode)
	{
		if (processorNode->getItem()->getCurrentTime() > maxTime)
		{
			maxTime = processorNode->getItem()->getCurrentTime();
			maxprocessor = processorNode->getItem();
		}
		if (processorNode->getItem()->getCurrentTime() < minTime)
		{
			minTime = processorNode->getItem()->getCurrentTime();
			minprocessor = processorNode->getItem();
		}
		processorNode = processorNode->getNext();
	}

	while ((static_cast<float>(maxTime - minTime) / maxTime) > 0.4)
	{
		if (minprocessor != nullptr && maxprocessor != nullptr && maxprocessor != minprocessor)
		{
			Process* process = maxprocessor->getTopElem();
			if (!process)
			{
				return;
			}
			while (process->isForked())
			{
				maxprocessor->moveToRDY(process);
				process = maxprocessor->getTopElem();
			}

			minprocessor->moveToRDY(process);
			maxTime = maxprocessor->getCurrentTime();
			minTime = minprocessor->getCurrentTime();
			cout << "task being stolen \n";
		}
		else
		{
			return;
		}
	}
}

bool Scheduler::migratedMaxW(Process* const& prcs)
{
	if (!prcs || prcs->isForked())
	{
		return false;

	}
	int ct = prcs->getCT();
	if (ct < this->MaxW)
	{
		return false;
	} // find a rr queue
	bool foundRR = false;
	Node<Processor*>* processorNode = Processors.getHead();
	while (processorNode)
	{
		Processor* prcsr = processorNode->getItem();
		if (!prcsr)
		{
			return false;
		}
		RR* rr_ptr = dynamic_cast<RR*>(prcsr);
		if (!rr_ptr)
		{
			processorNode = processorNode->getNext();
			continue;
		}
		rr_ptr->moveToRDY(prcs);
		rr_ptr->incrementCurrentTime(prcs->getCT());
		foundRR = true;
		break;
	}
	if (foundRR)
	{
		cout << "RR migration found\t" << prcs->getPID() << "\n";
	}
	return foundRR;
}

bool Scheduler::migratedRTF(Process* const& prcs) // checks processor_time under rft (Threshold)
{
	if (!prcs || prcs->isForked())
	{
		return false;
	}
	int ct = prcs->getCT();
	if (ct > this->RTF)
	{
		return false;
	} // find a sjf queue
	bool foundSJF = false;

	Node<Processor*>* processorNode = Processors.getHead();
	while (processorNode)
	{
		Processor* prcsr = processorNode->getItem();
		if (!prcsr)
		{
			return false;
		}
		SJF* sjf_ptr = dynamic_cast<SJF*>(prcsr);
		if (!sjf_ptr)
		{
			processorNode = processorNode->getNext();
			continue;
		}
		prcsr->moveToRDY(prcs);
		prcsr->incrementCurrentTime(prcs->getCT());
		foundSJF = true;
		break;
	}
	if (foundSJF)
	{
		cout << "SJF migration found\t" << prcs->getPID() << "\n";
	}
	return foundSJF;
}

int Scheduler::getForkProb()
{
	return forkProb;
}

void Scheduler::killSignal()
{
	Node<Pair<int, int>>* mapHead = SIGKILL_MAP.getHead();
	bool found = false;
	while (mapHead) {
		if (mapHead->getItem().getKey() == timestep)
		{
			int pid = mapHead->getItem().getValue();
			Node<Processor*>* headProcessor = Processors.getHead();
			bool found_process = false;
			Process* tmpProcess = nullptr;
			while (headProcessor)
			{
				FCFS* tempFCFS = dynamic_cast<FCFS*>(headProcessor->getItem());
				if (!tempFCFS)
				{
					headProcessor = headProcessor->getNext();
					continue;
				}

				tmpProcess = tempFCFS->findProcess(pid);
				if (tmpProcess)
				{
					found_process = true;
					break;
				}
				headProcessor = headProcessor->getNext();
			}

			if (found_process)
			{
				// tmpProcess->killOrph();
				TRM.enqueue(tmpProcess);
				cout << "Killsig found! \n\n\n\n";
			}
		}
		mapHead = mapHead->getNext();
	}
}


Process* Scheduler::ForkProcess(int child_ct)
{
	// generating the child:
	// assuming the pids max out the number of proccesses as shown in sample test file
	int child_pid = ((rand() % total_nprocess) + 1) + total_nprocess;
	Map<int, int> empty_io_map;
	empty_io_map.addPair(0, 0);
	Process* Child = new Process(child_pid, timestep, child_ct, empty_io_map);
	Child->setForked();
	// scheduling the child:
	Node<Processor*>* processorNode = this->Processors.getHead();
	if (!processorNode)
	{
		delete Child;
		return nullptr;
	}

	Processor* minProcessor = nullptr;
	int minTime = INT_MAX;

	while (processorNode)
	{
		Processor* tempProcessor = processorNode->getItem();
		if (!tempProcessor)
		{
			processorNode = processorNode->getNext();
			continue;
		}

		FCFS* tempFCFS = dynamic_cast<FCFS*>(tempProcessor);

		if (tempFCFS && (processorNode->getItem()->getCurrentTime() < minTime))
		{
			minTime = processorNode->getItem()->getCurrentTime();
			minProcessor = processorNode->getItem();
		}

		processorNode = processorNode->getNext();
	}

	if (minProcessor)
	{
		total_nprocess++;
		minProcessor->moveToRDY(Child);
		return Child;
	}
	else
	{
		delete Child;
		return nullptr;
	}

}
