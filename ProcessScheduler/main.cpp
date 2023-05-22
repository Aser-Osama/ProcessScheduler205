#include "Scheduler.h"
#include "ADT/PriorityQueue.h"

int main() {
	Scheduler* ProcessScheduler = Processor::getScheduler();
	ProcessScheduler->run();
	ProcessScheduler->save("output");
	//	ProcessScheduler.run();
	//	ProcessScheduler.

	return 0;
}