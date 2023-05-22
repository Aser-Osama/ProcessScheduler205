#include "Scheduler.h"
#include "ADT/PriorityQueue.h"

int main() {
	Scheduler* ProcessScheduler = Processor::getScheduler();
	ProcessScheduler->load("testfile");
	ProcessScheduler->run();
	//	ProcessScheduler.run();
	//	ProcessScheduler.

	return 0;
}