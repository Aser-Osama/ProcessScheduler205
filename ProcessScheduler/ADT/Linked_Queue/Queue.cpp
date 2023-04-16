#include "Queue.h"
#include "../../Process.h"
template<>
void Queue<Process*>::Print() const
{
	if (isEmpty())
		return;


	queuenode<Process*>* tmpPtr = frontPtr;

	while (tmpPtr)
	{
		cout << *(tmpPtr->getItem()) << ",\t";
		tmpPtr = tmpPtr->getNext();
	}
	cout << endl;
}
