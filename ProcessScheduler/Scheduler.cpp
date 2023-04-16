#include "Scheduler.h"

Scheduler::Scheduler(){}
Scheduler::~Scheduler(){}

Map<int,int> Scheduler::parseIO_R_D(string input){
    Map<int,int> output;
    bool mode=0;
    string k, v;

    for (int i=0; i<input.length();i++){
        if (input[i]=='('){
            k="";
            v="";
        }
        else if (input[i]==','){
            mode=!mode;
        }
        else if(input[i]==')'){
            output.addPair(stoi(k),stoi(v));
        }
        else{
            if (mode)
                v+=input[i];
            else
                k+=input[i];
        }

    }
    return output;
}



void Scheduler::load(string fileName){
    ifstream file;
    file.open(fileName);
    int NF, NS, NR, RRSlice;
    file>>NF; file>>NS; file>>NR; file>>RRSlice;

    for (int i=0; i<NF; i++){ 
        FCFS * temp = new FCFS();
        Processors.InsertEnd(temp); 
        }
    for (int i=0; i<NS; i++){ 
        SJF * temp = new SJF();
        Processors.InsertEnd(temp); 
        }
 
    for (int i=0; i<NR; i++){ 
        RR * temp = new RR(RRSlice);
        Processors.InsertEnd(temp); 
        }
    file>>RTF; file>>MaxW; file>>STL; file>>forkProb;

    int ProcessCount;
    file>>ProcessCount;

    for (int i=0; i<ProcessCount; i++){ 
        int AT, PID, CT, N;
        string IO_R_D_unparsed;
        file>>AT; file>>PID; file>>CT; file>>N;
        if (N!=0)file>>IO_R_D_unparsed;
        Map<int, int> IO_R_D;
        IO_R_D=parseIO_R_D(IO_R_D_unparsed);
        Process* temp = new Process(PID,AT,CT,IO_R_D);
        NEW.enqueue(temp); 
        } 

    while (!file.eof()){
        int time, PID;
        file>>time; file>>PID;
        SIGKILL.addPair(time,PID);
    }
}