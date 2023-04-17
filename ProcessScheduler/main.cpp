#include "Scheduler.h"
#include "ADT/PriorityQueue.h"

int main() {
	Scheduler ProcessScheduler("testfile");
	ProcessScheduler.simulator();
	//	ProcessScheduler.run();
	//	ProcessScheduler.save();

	return 0;
}