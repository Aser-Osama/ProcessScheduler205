#include "Scheduler.h"
#include "ADT/PriorityQueue.h"

int main() {
	Scheduler* ProcessScheduler = Processor::getScheduler();
	ProcessScheduler->run();
	//	ProcessScheduler.run();
	//	ProcessScheduler.save();

	return 0;
}