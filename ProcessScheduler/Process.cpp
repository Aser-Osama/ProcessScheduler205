#include "Process.h"

int Process::get_PID() { return PID; }
int Process::get_AT() { return AT; }
int Process::get_RT(){ return RT; }
int Process::get_CT(){ return CT; }
int Process::get_TT(){ return TT; }
int Process::get_TRT() { return TRT; }
int Process::get_WT() { return WT; }
Map Process::get_IO_R_D() { return IO_R_D; }

void Process::set_RT(int FT) { RT = FT - AT; } // FT stands for first time. for the timestep it enters the CPU
void Process::set_TT(int tt) { TT = tt; } // Termination Time should be set once
void Process::set_TRT(){ TRT = TT - AT; } // Turn around time should be set once
void Process::set_WT() { WT = TRT - CT; } // Wait time should be set once

Process::Process(int pid, int at, int ct, Map io_r_d):PID(pid),AT(at),CT(ct),IO_R_D(io_r_d), //initializer list to use while reading from file
													  TRT(0),WT(0),PS(NEW),TT(0) //values that are set as something initially
{
}