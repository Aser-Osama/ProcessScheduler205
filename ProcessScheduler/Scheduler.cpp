#include "Scheduler.h"


Scheduler::Scheduler(string filename)
{
	this->load(filename);
	StartingPoint = Processors.getHead();
}
Scheduler::~Scheduler() {}




void Scheduler::killOrphans(Process* P) {
	//P is a process that is about to terminate so you need to find if it has any children
	Node<Process*>* Head = (P->getChildren())->getHead();
	Node<Process*>* R = Head;
	Queue<Process*> TotalOrphans;
	if (P->getChildren()->getHead()) //if P has at least one child
	{
		//search for this child/children in rdy or run of fcfs processors
		
		while (Head) {
			TotalOrphans.enqueue(Head->getItem()); //add the child to orphans queue
			killOrphans(Head->getItem()); //
			Head = Head->getNext(); //get the sibling if any
		}
	}
	else {
		return;
	}
	// now that you collected all the children of P in Total Orphans
	// now if they are in rdy or run in any of fcfs processors, remove them from there
	// then move them to trm
	Node<Processor*>* headProcessor = Processors.getHead();
	Process* tmpProcess = nullptr;
	Process* temp = nullptr;
	while (headProcessor && TotalOrphans.dequeue(temp))
	{
		
		FCFS* tempFCFS = dynamic_cast<FCFS*>(headProcessor->getItem());
		if (!tempFCFS)
		{
			headProcessor = headProcessor->getNext();
			continue;
		}

		tmpProcess = tempFCFS->findProcess(temp->getPID());
		//
		if (tmpProcess)
		{
			TRM.enqueue(temp);
			break;
		}
		headProcessor = headProcessor->getNext();
	}

}


// A function that returns a node of the processor with the shortest queue
Node<Processor*>* Scheduler::ProcessorWithShortestQueue()
{
	Node<Processor*>* ProcessorWithShortestQueue = nullptr;
	Node<Processor*>* tempProcessor1 = Processors.getHead(); // Gets the first node of a processor from the Linked list
	ProcessorWithShortestQueue = tempProcessor1;

	Node<Processor*>* tempProcessor2 = tempProcessor1->getNext();
	if (!tempProcessor2) return tempProcessor1; // Checks if the list has two or more processors to compare between them

	while (tempProcessor2->getNext())
	{
		if (ProcessorWithShortestQueue->getItem()->getCurrentTime() > tempProcessor2->getItem()->getCurrentTime())
		{
			ProcessorWithShortestQueue = tempProcessor2;
		}
		tempProcessor2 = tempProcessor2->getNext();
	}
	// while loop stops at the last processor.
	// So, a comparison must be made between the last processor and ShortestQueue.

	if (ProcessorWithShortestQueue->getItem()->getCurrentTime() > tempProcessor2->getItem()->getCurrentTime())
		ProcessorWithShortestQueue = tempProcessor2;
	return ProcessorWithShortestQueue;
}

void Scheduler::NEWToRDY()
{
	Process* Process = nullptr;
	// If there is a process in the NEW list and its arrival time equals the currnent timestep
	while (NEW.peek(Process) && Process->getAT() == timestep)
	{
		NEW.dequeue(Process);
		Node<Processor*>* ProcessorWithShortestQueue = this->ProcessorWithShortestQueue();
		Process->setFT(timestep);
		ProcessorWithShortestQueue->getItem()->moveToRDY(Process);
		Process = nullptr;
	}
}

void Scheduler::BLKToRDY()
{
	Process* temp;
	if (!RUN_BLK && BLK.isEmpty()) return;
	if (!RUN_BLK)
	{
		BLK.dequeue(temp);
		RUN_BLK = temp;
	}
	if (RUN_BLK->decrementIO(timestep))
		return;
	else
	{
		Node<Processor*>* tempProcessor;
		tempProcessor = this->ProcessorWithShortestQueue();
		tempProcessor->getItem()->moveToRDY(temp);
	}
}
void Scheduler::RUNToTRM(Process* Prc)
{
	if (!Prc->subRemainingTime()) // Move the left to TRM when its CT reaches zero 
	{
		Prc->setTT(timestep);
		Prc->setTRT();
		Prc->setWT();
		this->killOrphans(Prc);

		TRM.enqueue(Prc);
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


void Scheduler::save(string name){
	ofstream file;
	file.open(name);
	file<<"TT\tPID\tAT\tCT\tIO_D\tWT\tRT\tTRT"<<endl;

	int sumWT(0), sumRT(0), sumTRT(0);

	Process * n;
	while(!TRM.isEmpty()){
		TRM.dequeue(n);
		n->setWT();

		int nTRT,nWT,nRT;
		nTRT=n->getTRT();nWT=n->getWT();nRT=n->getRT();
		sumTRT+=nTRT;sumWT+=nWT;sumRT+=nRT;

		file<<n->getTT()<<"\t"<<n->getPID()<<"\t"<<n->getAT()<<"\t";
		file<<n->getCTstored()<<"\t"<<n->getIO_R_D().sumMap() <<"\t\t"<<nWT<<"\t"<<nRT<<"\t"<<nTRT<<endl;
	}




	// loop through values


	file<<endl;
	file<<"Processes: "<<total_nprocess;

	file<<endl;
	file<<"Avg WT = "<<double(sumWT)/double(total_nprocess) <<",\tAvg RT = "<<double(sumRT)/double(total_nprocess) <<",\tAvg TRT = "<<double(sumTRT)/double(total_nprocess)<<endl;
	file<<"Migration %:"<<"RTF= "<< RTF <<"%,\t" <<"MaxW = "<<MaxW<<"%"<<endl;

	file<<"Work Steal %: "<< "value " << "%" << endl;
	file<<"Forked Process: "<<double(double(total_nprocess_forked)/double(total_nprocess))*100 <<"%"<<endl;
	file<<"Killed Process: "<< "value" << "%" << endl << endl;

	double Pnum=Processors.getCount();
	file<<"Processors: "<< Pnum<<" ["<< NF <<" FCFS, " << NS <<" SJF, "<< NR << " RR]"<<endl<<endl;
	file<<"Processors Load"<<endl;

	Node<Processor *> * p=Processors.getHead();
	for(int i=0;Pnum>i;i++){
		
		if (p->getItem()->getTotalTRT() != 0) {
			double load = (double(p->getItem()->getBusyTime() )/double( p->getItem()->getTotalTRT()))*100;
			file << "p" << i + 1 << "=" << load << "%";
		}
		else {
			file << "p" << i + 1 << "=" << 0 << "%";
		}
		if((i+1)%5!=0){
			file<<",\t";
		}
		else{
			file<<endl;
		}

		p=p->getNext();
	}
	
	file<<endl<<endl<<"Processors Utiliz"<<endl;

	p=Processors.getHead();
	double sumUtiliz=0;
	for(int i=0;Pnum>i;i++){
		double Utiliz=double(double(p->getItem()->getBusyTime())/(double(p->getItem()->getBusyTime())+double(p->getItem()->getIdleTime())))*100;
		sumUtiliz+=Utiliz ;
		file<<"p"<<i+1<<"="<<Utiliz<<"%";

		if((i+1)%5!=0){
			file<<",\t";
		}
		else{
			file<<endl;
		}

		p=p->getNext();
	}
	file<<endl;

	file<<"Avg utilization = "<< sumUtiliz/Pnum <<"%";


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

				this->RUNToTRM(tmp_prcs);
				tmp_prcs->setTRT();
				processorNode->getItem()->addTotalTRT(tmp_prcs->getTRT());
				/*tmp_prcs->setTT(timestep);
				tmp_prcs->setTRT();
				tmp_prcs->setWT();
				this->TRM.enqueue(tmp_prcs);*/
			}
			if (!proccess_complete && tmp_prcs) {

				this->BLK.enqueue(tmp_prcs);
			}
			if (processorNode->getItem()->getRUN()) {
				processorNode->getItem()->addBusyTime();

			}
			else {
				processorNode->getItem()->addIdleTime();
			}


			processorNode = processorNode->getNext();




		}

		MAIN_UI.UI_PICKER(true, timestep, Processors, BLK, TRM); // the print type will be based on user choice in phase 2
		timestep++;
	}

	MAIN_UI.UI_PICKER(false, timestep, Processors, BLK, TRM); // the print type will be based on user choice in phase 2
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
	Queue<Process*> tmp;
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

			if (process->isForked())
			{
				while (!maxprocessor->readyIsEmpty())
				{
					tmp.enqueue(process);
					process = maxprocessor->getTopElem();
					if (!process->isForked()) {
						break;
					}
				}
					//tmp.enqueue(process);

			}
			Process* temp_process;
				while (tmp.dequeue(temp_process)) {
						maxprocessor->moveToRDY(temp_process);
				}

			minprocessor->moveToRDY(process);
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
		foundRR = true;
		break;
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
		foundSJF = true;
		break;
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
	int pid = -1;
	while (mapHead) {
		if (mapHead->getItem().getKey() == timestep)
		{
			pid = mapHead->getItem().getValue();
			Node<Processor*>* headProcessor = Processors.getHead();
			bool found_process = false;
			Process* tmpProcess = nullptr;
			while (headProcessor)
			{
				FCFS* tempFCFS = dynamic_cast<FCFS*>(headProcessor->getItem());
				if (!tempFCFS)
				{
					headProcessor = headProcessor->getNext();
					break;
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
				this->killOrphans(tmpProcess);
				TRM.enqueue(tmpProcess);
			}
		}

			Node<Pair<int,int>>* next_node = mapHead->getNext();
			if (pid != -1)
				SIGKILL_MAP.deletePair(timestep, pid);
			mapHead = next_node;
			pid = -1;
	}
}


Process* Scheduler::ForkProcess(int child_ct)
{
	// generating the child:
	// assuming the pids max out the number of proccesses as shown in sample test file
	//int child_pid = ((rand() % total_nprocess) + 1) + total_nprocess;
	int child_pid = ((rand()) + 1);

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
		total_nprocess_forked++;
		minProcessor->moveToRDY(Child);
		return Child;
	}
	else
	{
		delete Child;
		return nullptr;
	}

}

void Scheduler::ProcessorOverheat(int timesteps)
{

}