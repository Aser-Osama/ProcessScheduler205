#include "Process.h"

int Process::get_PID() { return PID; }
int Process::get_AT() { return AT; }
int Process::get_RT(){ return RT; }
int Process::get_CT(){ return CT; }
int Process::get_TT(){ return TT; }
int Process::get_TRT() { return TRT; }
int Process::get_WT() { return WT; }
Map<int,int> Process::get_IO_R_D() { return IO_R_D; }

void Process::set_RT() { RT = FT - AT; } // FT stands for first time. for the timestep it enters the CPU
void Process::set_TT(int tt) { TT = tt; } // Termination Time should be set once
void Process::set_TRT(){ TRT = TT - AT; } // Turn around time should be set once
void Process::set_WT() { WT = TRT - CT; } // Wait time should be set once
bool Process::sub_LT() { if (LT > 0) { LT--; return 1; } else return 0; } // subtract from left over time. This returns false to show you when process is done
void Process::set_FT(int ft) { FT=ft; } // first time should be set during scheduler loop


Process::Process(int pid, int at, int ct, Map<int,int> io_r_d):PID(pid),AT(at),CT(ct),IO_R_D(io_r_d), //initializer list to use while reading from file
													  TRT(0),WT(0),TT(0),RT(0),FT(0),LT(ct) //values that are set as something initially
{
}