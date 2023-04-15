#include "Scheduler.h"
#include "ADT/Linked_Queue/Queue.h"
using namespace std;


int main() {

	Scheduler ProcessScheduler;
	ProcessScheduler.load("testfile");
//	ProcessScheduler.run();
//	ProcessScheduler.save();
	Queue<int> Test;
	Test.enqueue(1); 
	Test.enqueue(2);
	Test.enqueue(3);
	Test.enqueue(4);
	Test.enqueue(5);
	Test.enqueue(6);
	Test.enqueue(7);
	Test.Print();
	return 0;
}