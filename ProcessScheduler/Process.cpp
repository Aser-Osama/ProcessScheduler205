#include "Process.h"

int Process::TotalTRT = 0;
int Process::TotalWT = 0;

int Process::getPID() const { return PID; }
LinkedList<Process*>* Process::getChildren()const{ return children; }
int Process::getAT() const { return AT; }
int Process::getRT() const{ return RT; }
int Process::getCT() const{ return CT; }
int Process::getTT() const{ return TT; }
int Process::getTRT()const{ return TRT; }
int Process::getWT() const{ return WT; }
Map<int,int> Process::getIO_R_D() const { return IO_R_D; }

void Process::setRT(int ft) { RT = ft - AT; } // FT stands for first time. for the timestep it enters the CPU
void Process::setTT(int tt) { TT = tt; } // Termination Time should be set once
void Process::setTRT(){ TRT = TT - AT; } // Turn around time should be set once
void Process::setWT() { WT = TRT - CTstored; } // Wait time should be set once
bool Process::find_by_pid(int pid) { return this->PID == pid; }
int Process::getCTstored() const {return CTstored;}
bool Process::subRemainingTime()
{
	if (this->CT > 0) {
		this->CT--;
		return true;
	}
	else {
		return false;
	}
} // subtract from left over time. This returns false to show you when process is done
void Process::setCpuArrivalTime(int ft) { cpuArrivalTime=ft; } // first time should be set during scheduler loop


Process::Process(int pid, int at, int ct, Map<int,int> io_r_d):PID(pid),AT(at),CT(ct),IO_R_D(io_r_d), //initializer list to use while reading from file
													  TRT(0),WT(0),TT(0),RT(0),cpuArrivalTime(0),CTstored(ct) //values that are set as something initially
{
}

Process::Process(){}

ostream& operator<<(ostream& os, const Process& prcs)
{
	os << prcs.PID << " ";
	return os;
}

bool Process::operator==(const Process & p){
	if (p.getPID()==this->PID)
		return true;
	else
		return false;
}

bool Process::operator<(const Process& Process) const {
	return this->CT > Process.getCT();
}

bool Process::operator>(const Process& Process) const {
	return this->CT < Process.getCT();
}

void Process::addChild(Process* const& Child)
{
	children->InsertEnd(Child);
}

void Process::setForked()
{
	ForkedProcess = true;
}
bool Process::isForked()
{
	return ForkedProcess;
}

void Process::totalTRT(int ProcessTRT)
{
	TotalTRT += ProcessTRT;
}

void Process::totalWT(int ProcessWT)
{
	TotalWT += ProcessWT;
}

bool Process::decrementIO(int timestep) // Assumption: Processes IO are ordered in IO_R recieval asc in the input file 
{
	Node<Pair<int, int>>* ProcessIO = IO_R_D.getHead();
	if (ProcessIO->getItem().getValue() > 1) // When the process' IO is greater than 1
	{
		IO_R_D.updateValue(ProcessIO->getItem().getKey(), ProcessIO->getItem().getValue() - 1);
		return true; // The process does not finish IO 
	}
	else
	{
		IO_R_D.updateValue(ProcessIO->getItem().getKey(), ProcessIO->getItem().getValue() - 1);
		IO_R_D.deletePair(ProcessIO->getItem().getKey(), 0);
		return false; // The process finished its IO 
	}
}